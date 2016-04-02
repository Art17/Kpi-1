#include "client.h"
#include "cinemahall.h"

#include <stdlib.h>

struct tagClient_Private
{
    int maxSeat;
    int id;
    int seatNumber;
    int seatState;
};

int Client_getMaxSeat (Client* c)
{
    int status = 0;

    ErrorModule_setLastError(status);
    return c->cp->maxSeat;
}

int Client_initialize(Client* c, int maxSeat)
{
    static count = 0;
    int status = 0;

    Client_Private* cp = malloc (sizeof (Client_Private));

    if (cp == NULL)
    {
        status = 1;
        ErrorModule_setLastError(status);
        return status;
    }

    c->cp = cp;
    if (maxSeat <= 0 || maxSeat >= 32000)
    {
        status = 2;
        maxSeat = 10;
        ErrorModule_setLastError(status);
    }
    c->cp->maxSeat = maxSeat;
    c->cp->id = count++;
    c->cp->seatNumber = -1;
    c->cp->seatState = -1;

    ErrorModule_setLastError(status);
    return status;
}

int Client_getAction (Client* c, int* where, int* state)
{
    int status = 0;

    int s = rand () % 2 + 1;
    if (s == SEAT_BOOKED)
        s = rand () % 2 + 1;
    *state = s;
    *where = rand () % c->cp->maxSeat;

    ErrorModule_setLastError(status);
    return status;
}

int Client_getSeatState (Client* c)
{
    int status = 0;

    ErrorModule_setLastError(status);
    return c->cp->seatState;
}

int Client_deinitialize(Client* c)
{
    int status = 0;

    free (c->cp);

    ErrorModule_setLastError(status);
    return status;
}

int Client_getId (Client* c)
{
    int status = 0;

    ErrorModule_setLastError(status);
    return c->cp->id;
}

char* Client_errorCode_toString(int code)
{
    const char* errorStrings [] =
    {
        "All success",
        "Error allocating memory"
        "Error Invalid max seat"
    };
    const int errorSize = sizeof (errorStrings) / sizeof (char*);

    return errorStrings [code % errorSize];
}
