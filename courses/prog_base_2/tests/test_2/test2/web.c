#include "web.h"
#include "student.h"

struct web_s
{
    socket_t* serverSocket;
};

const char* answerFormat =
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n\r\n"
        "%s";
const char* requestFormat =
        "%s %s HTTP/1.1\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n\r\n"
        "%s";

void serverReply (web_t self, socket_t*, http_request_t);
void serverInfo (socket_t* clientSocket);
void serverMessagePage (socket_t* clientSocket, int code, const char* reason, const char* format, const char* text);
void serverExternal (socket_t*);

char* getMyInfo (char []);

char* getMyInfo (char buffer[])
{
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    doc = xmlNewDoc ("1.0");
    root_element = xmlNewNode (NULL, "students");
    xmlDocSetRootElement (doc, root_element);

    student_t st = student_new ();
    student_setValues (st, "Artem Saprykin 32");

    student_toXmlNode (st, doc, root_element);

    student_free (st);

    xmlChar* pMem = NULL;
    int size = 0;
    xmlDocDumpMemory(doc, &pMem, &size);

	strcpy(buffer, pMem);

    free(pMem);
    xmlFreeDoc (doc);
}

void serverInfo (socket_t* clientSocket)
{
    char info[256];

    getMyInfo (info);

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", "text/xml", strlen (info), info);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverExternal (socket_t* clientSocket)
{
    socket_t* thisClientSoc = socket_new ();
    socket_connect(thisClientSoc, "216.58.209.49", 80);

    char uri [256];

    strcpy (uri, "http://pb-homework.appspot.com/test/var/32?format=xml");

    char req [1024];

    sprintf (req, requestFormat, "GET", uri, NULL, NULL, NULL);

    socket_write(thisClientSoc, req, strlen (req));
    char responce [1024];
    socket_read (thisClientSoc, responce, 1024);

    int contentLength = 0;
    sscanf (strstr(responce, "Content-Length: ") + strlen ("Content-Length: "), "%d", &contentLength);
    char* data = strstr (responce, "\r\n\r\n") + 4;
    char buffer [1024];

    memcpy (buffer, data, contentLength);
    buffer[contentLength] = '\0';

    serverMessagePage (clientSocket, 200, "OK", "text/xml", buffer);

    socket_free(thisClientSoc);
}

void serverReply (web_t self, socket_t* clientSocket, http_request_t httpRequest)
{
    char method[MAX_METHOD];
    char uri [MAX_URI];

    http_request_getMethod(httpRequest, method);
    http_request_getUri (httpRequest, uri);

    if ( strcmp (method, "GET") == 0 )
    {
        if ( strcmp ( uri, "/info" ) == 0 )
            serverInfo (clientSocket);
        else  if ( strcmp ( uri, "/external" ) == 0 )
        {
            serverExternal (clientSocket);
        }
        else
            serverMessagePage(clientSocket, 404, "NOT FOUND", "text", "Wrong url");
    }
}

void serverOptions (socket_t* clientSocket)
{
    char strbuf [256];
    sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Access-Control-Allow-Origin: *\n"
            "Access-Control-Allow-Methods: DELETE\n"
            "\n");
    socket_write (clientSocket, strbuf, strlen (strbuf));
    socket_close(clientSocket);
}



void serverMessagePage (socket_t* clientSocket, int code, const char* reason, const char* format, const char* text)
{
    const char* temp = "%s";
    char message [2056];
    sprintf (message, temp, text);

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, code, reason, format, strlen (message), message);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}


web_t web_new ()
{
    web_t self = malloc ( sizeof (struct web_s) );
    memset (self, 0, sizeof (struct web_s));

    return self;
}

void web_createServer (web_t self, int port)
{
    self->serverSocket = socket_new();
    socket_bind(self->serverSocket, port);
}

void web_listen (web_t self)
{
    socket_listen (self->serverSocket);

    char szRequest [10000];
    const char* msg = "Hello world";
    while (1)
    {
        socket_t* clientSocket = socket_accept(self->serverSocket);
        socket_read(clientSocket, szRequest, sizeof (szRequest));

        http_request_t httpRequest = http_request_new ();
        http_request_parse (httpRequest, szRequest);

        serverReply (self, clientSocket, httpRequest);

        http_request_free (httpRequest);
    }
}

void web_free (web_t self)
{
    socket_close(self->serverSocket);
    free (self);
}
