#include "stack.h"
#include <time.h>
#include <stdlib.h>

#include "randstrings.h"

int addRandomString (Stack* s)
{
    StackPush (s, randomStrings [ rand () % arraySize ] );

    return 0;
}

int stackFullReaction (Stack* s)
{
    char buffer [256];

    for (int i = 0; i < 3; i++)
        StackPop (s, buffer);

    return 0;
}
