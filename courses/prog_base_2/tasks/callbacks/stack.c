#include <stdio.h>
#include "stack.h"

void initStack(Stack* s)
{
  s->stackPointer = 0;
}

void pushOntoStack(Stack* s, int number)
{
  s->stack[ s->stackPointer ] = number;
  (s->stackPointer)++;
}

int popFromStack(Stack* s)
{
  (s->stackPointer)--;
  return s->stack[ s->stackPointer ];
}

int stackEmpty(Stack* s)
{
  if (s->stackPointer > 0)
    return 0;    /* false - the stack is not empty */
  else
    return 1;    /* true */
}

int stackCount (Stack* s)
{
    return s->stackPointer;
}
