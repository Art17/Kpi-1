#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define MAX_STACK_SIZE 10

struct tagStackPrivate
{
    int top;
    char array[MAX_STACK_SIZE][256];
};

void StackInitialize(Stack* s)
{
    s->sp = (StackPrivate*)malloc ( sizeof (StackPrivate) );
    memset (s->sp, 0, sizeof (StackPrivate));

}

void StackDeinitialize (Stack* s)
{
    free (s->sp);
}

int StackPush (Stack* s, const char* str)
{
    if (s->sp->top == MAX_STACK_SIZE)
    {
        return 1;
    }

    strcpy (s->sp->array[s->sp->top++], str);

    return 0;
}

char* StackPop (Stack* s, char str[])
{
    if (s->sp->top == 0)
        return NULL;

    strcpy (str, s->sp->array[s->sp->top--]);

    return str;
}

char* StackPeek (Stack* s, char str[])
{
    if (s->sp->top == 0)
        return NULL;

    strcpy (str, s->sp->array[s->sp->top]);

    return str;
}

int StackgetCount (Stack* s)
{
    return s->sp->top;
}

int StackFree (Stack* s)
{
    s->sp->top = 0;

    return 0;
}

int StackIsEmpty (Stack* s)
{
    return s->sp->top == 0;
}

int StackIsFull (Stack* s)
{
    return s->sp->top == MAX_STACK_SIZE;
}

void StackPrint (Stack* s)
{
    for (int i = 0; i < s->sp->top; i++)
        printf ("%s\n", s->sp->array[i]);
}
