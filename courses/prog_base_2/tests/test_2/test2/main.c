#include <stdio.h>
#include <stdlib.h>

#include "web.h"
#include "libsocket/socket.h"

int main()
{
    lib_init ();

    web_t myServer = web_new ();
    int port = 5000;
    web_createServer(myServer, port);

    printf ("server started with port %d", port);

    web_listen (myServer);

    lib_free ();

    return 0;
}
