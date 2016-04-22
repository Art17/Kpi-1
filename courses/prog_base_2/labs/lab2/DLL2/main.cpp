#include "main.h"
#include "stack.h"

// a sample exported function
void DLL_EXPORT addString(Stack* s)
{
    const int length = 15;
    char buffer[length];

    int i = 0;
    for (; i < rand () % 10 + 1; i++)
        buffer[i] = (rand () % ((int)'z' - (int)'a' + 1)) + 'a';
    buffer[i++] = '\0';

    StackPush (s, buffer);

}

void DLL_EXPORT stackFullReaction(Stack* s)
{
    char buffer [256];
    StackPeek(s, buffer);
    int q = strlen (buffer);

    printf ("deleting %d elements: \n", q);

    for (int i = 0; i < q; i++)
        StackPop (s, buffer);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
