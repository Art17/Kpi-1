#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

const int WIDTH = 80;
const int HEIGHT = 25;

void drawPoint (int x, int y, char c, int attr)
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
    char c = '\0';

    int x0 = 40, y0 = 12;
    double scaleX = 0.1, scaleY = 0.4;

    do
    {
        system ("cls");

        switch (c)
        {
        case 'a':
            x0--;
            break;
        case 'd':
            x0++;
            break;
        case 'w':
            y0--;
            break;
        case 's':
            y0++;
            break;
        case 'z':
            scaleX -= 0.05;
            break;
        case 'c':
            scaleX += 0.05;
            break;
        case 'e':
            scaleY += 0.05;
            break;
        case 'q':
            scaleY -= 0.05;
            break;
        }

        x0 = min (x0, WIDTH-1);
        x0 = max (0, x0);

        y0 = min (y0, HEIGHT-1);
        y0 = max (0, y0);


        int i = 0;
        double t = 0;

        printf ("f(x) = sin(x^2) + cos(x)^2\n");
        printf ("f(x) = 2/(3x + 3)");

        for (i = 0; i < WIDTH; i++)
            if (abs((x0-i)) % max((int)(1./scaleX), 1) == 0)
                drawPoint (i, y0, '|', FOREGROUND_WHITE);
            else
                drawPoint (i, y0, '-', FOREGROUND_WHITE);
        for (i = 0; i < HEIGHT; i++)
            if (abs((y0-i)) % max((int)(1./scaleY), 1) == 0)
                drawPoint (x0, i, '-', FOREGROUND_WHITE);
            else
                drawPoint (x0, i, '|', FOREGROUND_WHITE);

        drawPoint (x0, y0, '*', FOREGROUND_BLUE);

        for (i = 0; i < WIDTH; i++)
        {
            t = (i-x0)*scaleX;
            drawPoint (i,
                  y0 - ( sin(t*t) + cos(t)*cos(t) )/scaleY,
                  '*',
                  FOREGROUND_GREEN);
            drawPoint (i,
                  y0 - ( 2/(3*t + 3))/scaleY,
                  '*',
                  FOREGROUND_YELLOW);
    }
    } while (c = getch ());

    return 0;
}
