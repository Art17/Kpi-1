#include "main.h"

// a sample exported function
void DLL_EXPORT addString(Stack* s)
{
    char buffer[256];

    printf ("Write string: ");
    fflush (stdin);
    gets (buffer);
    StackPush (s, buffer);
}

void DLL_EXPORT stackFullReaction(Stack* s)
{
    char buffer [256];
    int num = 0;

    printf ("write number of strings to delete: ");
    scanf ("%d", &num);

    for (int i = 0; i < num; i++)
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
