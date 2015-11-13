#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

void draw (int x, int y, char c, int attr)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleTextAttribute(hConsole, attr);
    SetConsoleCursorPosition(hConsole, pos);
    printf ("%c", c);
}

int main()
{
    const int WIDTH = 80;
    const int HEIGHT = 25;

    int i = 0;
    double t = 0;

    int x0 = 40, y0 = 12;
    double scaleX = 0.1, scaleY = 0.4;

    if (x0 > 79 || x0 < 0 || y0 < 0 || y0 > 24)
    {
        printf ("cat");
        return 0;
    }
    printf ("f(x) = sin(x^2) + cos(x)^2\n");
    printf ("f(x) = 2/(3x + 3)");

    for (i = 0; i < WIDTH; i++)
        if (abs((x0-i)) % max((int)(1./scaleX), 1) == 0)
            draw (i, y0, '|', FOREGROUND_WHITE);
        else
            draw (i, y0, '-', FOREGROUND_WHITE);
    for (i = 0; i < HEIGHT; i++)
        if (abs((y0-i)) % max((int)(1./scaleY), 1) == 0)
            draw (x0, i, '-', FOREGROUND_WHITE);
        else
            draw (x0, i, '|', FOREGROUND_WHITE);

    draw (x0, y0, '*', FOREGROUND_BLUE);

    for (i = 0; i < WIDTH; i++)
    {
        t = (i-x0)*scaleX;
        draw (i,
              y0 - ( sin(t*t) + cos(t)*cos(t) )/scaleY,
              '*',
              FOREGROUND_GREEN);
        draw (i,
              y0 - ( 2/(3*t + 3))/scaleY,
              '*',
              FOREGROUND_YELLOW);
    }

    Sleep(1000000);

    return 0;
}
