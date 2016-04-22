#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "stack.h"
#include "staticlib.h"

typedef int (*add_f)(Stack* );
typedef void (*react_f)(Stack* );

typedef struct dynamic_s {
    HANDLE hLib;
    add_f add;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();

int main()
{
    srand (time (NULL));

    Stack s;

    StackInitialize(&s);

    while (!StackIsFull(&s))
    {
        addRandomString(&s);
    }

    printf ("---------------------Stack is full with values: ------------\n\n");
    StackPrint (&s);

    printf ("\n\n---------------------Static lib reation ... ----------------\n\n");

    stackFullReaction(&s);

    StackPrint (&s);

    printf ("--------------------------------------------------------------------\n\n");

    const char * dllName = userChoice();

    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->add) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");

    while (1)
    {
        dll->add (&s);
        if (StackIsFull(&s))
        {
            printf ("\n\n----------------Stack is full with values-------------------\n\n");
            StackPrint (&s);
            printf ("\n\n----------------Dll reaction---------------------------------\n");
            dll->react (&s);
            printf ("\n-----------------Stack values--------------------------------\n\n");
            StackPrint (&s);

            printf ("\n\n\n\n");
            getch ();
        }
    }

    StackDeinitialize (&s);

    return 0;
}

const char * userChoice()
{
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "dlls\\DLL1.dll";
        } else if (dllNum == 2) {
            return "dlls\\DLL2.dll";
        }
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->add = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->add = (add_f)GetProcAddress(dyn->hLib, "addString");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "stackFullReaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
