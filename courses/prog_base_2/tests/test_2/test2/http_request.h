#ifndef HTTP_REQUEST_H_INCLUDED
#define HTTP_REQUEST_H_INCLUDED

#define MAX_METHOD 8
#define MAX_URI 256
#define MAX_KEY 256
#define MAX_VALUE 256
#define MAX_FORM 15

#include <stdlib.h>

typedef struct http_request_s* http_request_t;

http_request_t http_request_new ();

void http_request_parse (http_request_t, const char* );

char* http_request_getMethod (http_request_t, char []);
char* http_request_getUri (http_request_t, char []);

char* http_request_getKey (http_request_t, int, char []);
char* http_request_getValue (http_request_t, const char*, char []);
int http_request_getArgsNum (http_request_t);

void http_request_free (http_request_t );

#endif // HTTP_REQUEST_H_INCLUDED
