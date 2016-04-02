#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include "cinemahall.h"
#include <windows.h>

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
#define BACKGROUND_WHITE BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED

#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY

#define BACKGROUND_GRAY BACKGROUND_INTENSITY

typedef struct tagConsole_Private Console_Private;

typedef struct
{
    Console_Private* cp;
} Console;

int Console_initialize (Console*, int, int);
int Console_deinitialize (Console*);

int Console_getSize (Console*, COORD*);
int Console_showCinema (Console*);

static int Console_setPosition (Console*, int, int);
static int Console_printSymbol (Console*, char, int);

int Console_showCinemaHall (Console*, CinemaHall* );

char* Console_errorCode_toString (int);

#endif // CONSOLE_H_INCLUDED
