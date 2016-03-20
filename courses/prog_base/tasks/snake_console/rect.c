#include "rect.h"

Rect getRect (int x1, int y1, int x2, int y2)
{
    Rect r;
    r.x1 = x1;
    r.y1 = y1;
    r.x2 = x2;
    r.y2 = y2;

    return r;
}

void drawRect (const Rect* r)
{
    for (int x = (*r).x1; x < (*r).x2; x++)
        for (int y = (*r).y1; y < (*r).y2; y++)
        {
            setPos (x, y);
            printf (" ");
        }
}
