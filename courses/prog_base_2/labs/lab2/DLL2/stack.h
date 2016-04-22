#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdlib.h>

typedef struct tagStackPrivate StackPrivate;

typedef struct
{
    StackPrivate* sp;
} Stack;

void StackInitialize (Stack*);
void StackDeinitialize (Stack*);

int StackPush (Stack*, const char*);
char* StackPop (Stack*, char[]);
char* StackPeek (Stack*, char[]);

int StackIsEmpty (Stack* );
int StackIsFull (Stack* );

int StackGetCount (Stack*);

int StackFree (Stack*);

void StackPrint (Stack*);

#endif // STACK_H_INCLUDED
