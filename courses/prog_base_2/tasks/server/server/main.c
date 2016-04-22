#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define CRLF "\r\n"

#define MAX_URI_LENGTH 200
#define MAX_HEADERS 50

#define MAX_CLIENTS 1000
#define N_EVENTS 10
#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct HTTPHeader {
  char *name;
  char *value;
} HTTPHeader;

typedef enum ParseError{
  NO_ERRORS,
  BAD_METHOD_SEPARATOR,
  BAD_REQ_START,
} ParseError;

typedef enum ParseStatus {
  PARSE_START,
  PARSE_SKIP_EMPTY_LINES_LF,
  PARSE_SKIP_EMPTY_LINES_CR,
  PARSE_METHOD,
  PARSE_URI,
  PARSE_STATUS,
  PARSE_HEADERS,
  READ_BODY,
  PARSED
} ParseStatus;

typedef enum HTTPMethod { GET, POST, DELETE, METHOD_UNDEFINED } HTTPMethod;

typedef struct HTTPRequest {
  ParseError error;
  char parse_buff[1024];
  size_t parse_buff_pos;

  ParseStatus status;

  HTTPMethod method;
  char uri[MAX_URI_LENGTH];
  HTTPHeader headers[MAX_HEADERS];
  size_t n_headers;

  char *body;
  size_t body_length;
} HTTPRequest;

void init_header(HTTPHeader *ret, char *name, char *value) {
  ret->name = name;
  ret->value = value;
}

void deinit_header(HTTPHeader *h) {
  free(h->name);
  free(h->value);
}

HTTPRequest *new_req() {
  HTTPRequest *ret = malloc(sizeof(HTTPRequest));
  ret->error = NO_ERRORS;
  ret->parse_buff_pos = 0;
  ret->status = PARSE_START;
  ret->method = METHOD_UNDEFINED;
  ret->uri[0] = '\0';
  ret->n_headers = 0;
  ret->body = NULL;
  ret->body_length = 0;
  return ret;
}

bool req_feed(HTTPRequest *req, char feeder[], size_t n) {
  while (n > 0) {
    switch (req->status) {

    case PARSE_START:
    case PARSE_SKIP_EMPTY_LINES_CR:
      if(*feeder == '\r'){
	req->status = PARSE_SKIP_EMPTY_LINES_LF;
        feeder++;
	n--;
      }
      else req->status = PARSE_METHOD;
      break;

    case PARSE_SKIP_EMPTY_LINES_LF:
      if(*feeder == '\n'){
	req->status = PARSE_SKIP_EMPTY_LINES_CR;
	feeder++;
	n--;
      }
      break;

    case PARSE_METHOD:
      while(isalpha(*feeder) && n > 0){
	req->parse_buff[req->parse_buff_pos++] = *feeder;
	n--;
	feeder++;
      }
      if(*feeder==' ') {
	memcpy(req->method, req->parse_buff, req->parse_buff_pos);
	req->parse_buff[req->parse_buff_pos] = '\0';
	req->parse_buff_pos = 0;
	req->status = PARSE_URI;
	feeder++;
	n--;
	continue;
      } else {
	req->error = BAD_METHOD_SEPARATOR;
	return false;
      }
      break;

    case PARSE_URI:
      while(*feeder != ' ' && n > 0){
	req->parse_buff[req->parse_buff_pos++] = *feeder;
	feeder++;
	n--;
      }

      break;
    }
  }
  return true;
}

void free_req(HTTPRequest *req) {
  for (size_t i = 0; i < req->n_headers; i++)
    deinit_header(&req->headers[i]);
  free(req->body);
}

int setnonblock(int fd) {
  int flags;

  flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    fputs("Can't get flags\n", stderr);
    return -1;
  }

  if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
    fputs("Can't set O_NONBLOCK\n", stderr);
    return -1;
  }

  return fd;
}

int create_in_listener_nb(int port) {
  struct sockaddr_in addr;
  int fd;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    fputs("Can't create socket\n", stderr);
    return -1;
  }

  if (setnonblock(fd) == -1) {
    fputs("Can't make socket nonblocking\n", stderr);
    return -1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    fputs("Can't bind\n", stderr);
    return -1;
  }

  return fd;
}

int main(void) {
  int listener_fd, epoll_fd;
  int clients_fds[MAX_CLIENTS];
  size_t n_clients;
  struct epoll_event ev;
  struct epoll_event events[N_EVENTS];
  int got_events;

  n_clients = 0;

  listener_fd = create_in_listener_nb(8081);
  if (listener_fd == -1) {
    fputs("Can't create listener", stderr);
    exit(EXIT_FAILURE);
  }

  epoll_fd = epoll_create1(0);

  // Add listener to epoll
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = listener_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener_fd, &ev) == -1) {
    fputs("Can't add listener to epoll", stderr);
    goto EXIT;
  };

  listen(listener_fd, SOMAXCONN);

  while (1) {
    int i;
    got_events = epoll_wait(epoll_fd, events, N_EVENTS, -1);
    for (i = 0; i < got_events; i++) {
      if (events[i].data.fd == listener_fd &&
          events[i].events & EPOLLIN) { /*Got accept*/
        int accepted_fd;
        accepted_fd = accept(listener_fd, NULL, NULL);
        printf("Connected %d\n", accepted_fd);
        setnonblock(accepted_fd);

        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = accepted_fd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, accepted_fd, &ev);
      } else if (events[i].events & EPOLLIN) { // Got something from client
        ssize_t got_len;
        char got_buff[1000];

        printf("Got something from %d\n", events[i].data.fd);
        got_len = recv(events[i].data.fd, got_buff, LEN(got_buff) - 1, 0);
        got_buff[got_len] = '\0';
        puts(got_buff);
      }
    }
  }

EXIT:
  close(listener_fd);
  close(epoll_fd);
  exit(EXIT_FAILURE);
}
