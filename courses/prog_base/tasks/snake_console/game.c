#include "game.h"

void mainMenu ()
{
    Rect r;
    int kx = 25;
    int ky = 5;
    r = getRect (WIDTH/2 - kx, HEIGHT/2 - ky, WIDTH/2 + kx, HEIGHT/2 + ky);
    setBackgroundColor (BACKGROUND_WHITE);
    drawRect (&r);

    setForegroundColor(FOREGROUND_BLUE);

    char* str = "Main Menu";
    kx = strlen (str)/2;

    setPos ((r.x2-r.x1)/2 + r.x1 - kx, r.y1);
    printf ("Main Menu");

    setForegroundColor(FOREGROUND_GREEN);

    setPos (r.x1 + 2, r.y1 + fontSize);
    printf ("1. play");

    setPos (r.x1 + 2, r.y1 + 2*fontSize);
    printf ("2. record table");

    setPos (r.x1 + 2 + 20, r.y1 + 2*fontSize);

    int posy [] = {r.y1 + fontSize, r.y1 + 2*fontSize};

    while (1)
    {
        int c = getch ();
        switch (c)
        {
        case UP:
            setPos (r.x1 + 2 + 20, posy[0]);
            break;
        case DOWN:
            setPos (r.x1 + 2 + 20, posy[1]);
            break;
        case ENTER:
            if (getYPos == posy[0])
                0;//play ();
            if (getYPos == posy[1])
                0;//recordTable ();
            break;
        }
    }
}
