#include "console.h"

void init ()
{
    char params[256];
    sprintf (params, "mode con cols=%d lines=%d", WIDTH, HEIGHT);

    system(params);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void setBackgroundColor (int newColor)
{
    backgroundColor = newColor;
    attr = backgroundColor | foregroundColor;
    SetConsoleTextAttribute(hConsole, attr);
}

void setForegroundColor (int newColor)
{
    foregroundColor = newColor;
    attr = foregroundColor | backgroundColor;
    SetConsoleTextAttribute(hConsole, attr);
}

void clearScreen ()
{
    system ("cls");
}

void setPos (int x, int y)
{
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);

}

int getYPos ()
{
    return pos.Y;
}

int getXPos ()
{
    return pos.X;
}

