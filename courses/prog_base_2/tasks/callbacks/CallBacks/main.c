#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include <windows.h>

typedef int (*cb)(Stack*);

void stackProcess (cb checkCB, cb processCB)
{
    Stack s;
    initStack(&s);

    while (1)
    {
        int x = rand () % 15545 - 1000;
        pushOntoStack (&s, x);
        printf ("pushed to stack: %d\n", x);
        if ( checkCB (&s) )
            processCB (&s);
    }
}

int checkCB (Stack* s)
{
    if (stackCount(s) > 10 && stackCount(s) < 20)
        return 1;
    return 0;
}

int processCB (Stack* s)
{
    for (int i = 0; i < 5; i++)
    {
        int x = popFromStack (s);
        printf ("popped from stack: %d\n", x);
    }
    return 0;
}

int main()
{
    srand ( time (NULL) );

    stackProcess (checkCB, processCB);
    return 0;
}
