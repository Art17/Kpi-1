#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <windows.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#define BACKGROUND_YELLOW BACKGROUND_RED | BACKGROUND_GREEN
#define BACKGROUND_WHITE  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE

const int WIDTH = 108;
const int HEIGHT = 36;

int foregroundColor = FOREGROUND_WHITE;
int backgroundColor = 0;
int attr = (0 | FOREGROUND_WHITE);
int fontSize = 2;
COORD pos;

HANDLE hConsole;

void init ();
void clearScreen ();
void setBackgroundColor (int);
void setForegroundColor (int);
void setPos (int, int);
void setFont (int, int);
int getXPos ();
int getYPos ();

#endif // CONSOLE_H_INCLUDED
