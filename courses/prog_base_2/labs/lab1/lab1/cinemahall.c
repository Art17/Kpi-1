#include "cinemahall.h"
#include "errormodule.h"
#include <stdlib.h>

struct tagCinemaHall_Private
{
    int* cinemaArray;
    int cinemaSize;
};

int CinemaHall_initialize (CinemaHall* ch , int size)
{
    int status = 0;

    CinemaHall_Private* chp = malloc (sizeof (CinemaHall_Private));
    if (chp == NULL)
    {
        status = 2;
        ErrorModule_setLastError(status);
        return status;
    }
    ch->chp = chp;
    if (size <= 0 || size > 32000)
    {
        status = 1;
        ErrorModule_setLastError(status);
        size = 10;
    }
    int* array = malloc (size*sizeof(int));
    if (array == NULL)
    {
        status = 2;
        ErrorModule_setLastError(status);
        return status;
    }
    memset (array, 0, size*sizeof(int));
    ch->chp->cinemaArray = array;
    ch->chp->cinemaSize = size;

    ErrorModule_setLastError(status);

    return status;
}
int CinemaHall_deinitialize (CinemaHall* ch)
{
    int status = 0;

    free (ch->chp->cinemaArray);
    free (ch->chp);

    ErrorModule_setLastError(status);
    return status;
}

int CinemaHall_getQuantity (CinemaHall* ch)
{
    int status = 0;

    ErrorModule_setLastError(status);
    return ch->chp->cinemaSize;
}

int CinemaHall_getSeatState (CinemaHall* ch, int where)
{
    int status = 0;

    if (where < 0 || where >= ch->chp->cinemaSize)
    {
        status = 3;
        ErrorModule_setLastError(status);
        return -1;
    }

    ErrorModule_setLastError(status);
    return ch->chp->cinemaArray[where];
}
int CinemaHall_setSeatState (CinemaHall* ch, int where, int state)
{
    int status = 0;

    if (where < 0 || where >= ch->chp->cinemaSize)
    {
        status = 3;
        ErrorModule_setLastError(status);
        return -1;
    }

    int prev = ch->chp->cinemaArray[where];
    ch->chp->cinemaArray[where] = state;

    ErrorModule_setLastError(status);
    return prev;
}

char* CinemaHall_errorCode_toString (int code)
{
    const char* errorStrings [] =
    {
        "All success",
        "Invalid cinema size",
        "Error allocating memory",
        "Invalid place",
    };
    const int errorSize = sizeof (errorStrings) / sizeof (char*);

    return errorStrings [code % errorSize];
}
