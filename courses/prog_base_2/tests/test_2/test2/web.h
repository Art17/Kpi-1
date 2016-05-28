#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

#include "libsocket/socket.h"
#include <stdlib.h>
#include "http_request.h"
#include "student.h"
#include "progdata.h"

typedef struct web_s* web_t;

web_t web_new ();
void web_createServer (web_t, int port);

void web_listen (web_t);

void web_free (web_t);

#endif // WEB_H_INCLUDED
