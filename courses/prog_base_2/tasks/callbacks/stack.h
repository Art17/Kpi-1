#ifndef stack_h
#define stack_h

#define MAX_STACK_SIZE        1000

typedef struct
{
  int stack[MAX_STACK_SIZE];
  int stackPointer;
}
Stack;

void initStack(Stack* s);
void pushOntoStack(Stack* s, int number);
int popFromStack(Stack* s);
int stackEmpty(Stack* s);
int stackCount (Stack* s);

#endif
