#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

typedef struct tagRect
{
    int x1, y1;
    int x2, y2;
} Rect;

Rect getRect (int, int, int, int);
void drawRect (const Rect*);

#endif // RECT_H_INCLUDED
