#include <stdio.h>
#include <windows.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

void draw (int x, int y, int attr)
{
    static double k = 1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleTextAttribute(hConsole, attr);
    SetConsoleCursorPosition(hConsole, pos);
    printf ("*");
    k+=0.025;
    Sleep (5);
}

int main ()
{
    int x, y;
    int colors[] = {FOREGROUND_GREEN, FOREGROUND_WHITE, FOREGROUND_YELLOW, FOREGROUND_GREEN};
    int clr = 0;

    x = 79;
    y = 0;

    draw (x, y, colors[clr++%4]);

    while (!(x == 0 && y == 23))
    {

        x--;
        if (x >= 0)
            draw (x, y, colors[clr%4]);
        while (x < 79 && y < 24)
            x++, y++, draw (x, y, colors[clr%4]);

        if (y == 24)
            x--;
        else
            y++;
        clr++;
        draw (x, y, colors[clr%4]);
        while (y > 0 && x > 0)
            x--, y--, draw (x, y, colors[clr%4]);
        clr++;
    }

}
