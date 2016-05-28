#include "http_request.h"

struct KeyValue_s
{
    char key [MAX_KEY];
    char value [MAX_VALUE];
};

typedef struct KeyValue_s KeyValue;

struct http_request_s
{
    char method [MAX_METHOD];
    char uri [MAX_URI];

    KeyValue form[MAX_FORM];
    int argsLength;
};

http_request_t http_request_new ()
{
    http_request_t self = malloc ( sizeof (struct http_request_s) );
    memset (self, 0, sizeof (struct http_request_s));

    return self;
}

void http_request_parse (http_request_t self, const char* szRequest)
{
    char buffer [1000];
    sscanf (szRequest, "%s %s", self->method, self->uri);

    if ( strcmp (self->method, "POST") == 0 )
    {
        char* formPtr = strstr (szRequest, "\r\n\r\n") + 4;

        char formBuff[1000];
        strcpy(formBuff, formPtr);
        // ---
        self->argsLength = 0;
        char* tok;
        for(tok = strtok(formBuff, "&"); tok != NULL; tok = strtok(NULL, "&")){
            size_t keyLen = strstr(tok, "=") - tok;
            memcpy(self->form[self->argsLength].key, tok, keyLen);
            self->form[self->argsLength].key[keyLen] = '\0';

            strcpy(self->form[self->argsLength].value, tok + keyLen + 1);

            self->argsLength++;
        }
        // ---
    }
}

char* http_request_getKey (http_request_t self, int index, char buffer[])
{
    strcpy (buffer, self->form[index].key);

    return buffer;
}
char* http_request_getValue (http_request_t self, const char* key, char buffer[])
{
    for (int i = 0; i < self->argsLength; i++)
        if ( strcmp (self->form[i].key, key) == 0 )
            strcpy (buffer, self->form[i].value);

    return buffer;
}

int http_request_getArgsNum (http_request_t self)
{
    return self->argsLength;
}

char* http_request_getMethod (http_request_t self, char buffer[])
{
    strcpy (buffer, self->method);

    return buffer;
}

char* http_request_getUri (http_request_t self, char buffer[])
{
    strcpy (buffer, self->uri);

    return buffer;
}

void http_request_free (http_request_t self)
{
    free (self);
}
