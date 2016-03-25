#include "randomizer.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int RandomizerInitialize(Randomizer* r, int* a)
{
    srand (time (NULL));
    r->a = a;

    return 0;
}

int RandomizerDeinitialize (Randomizer* r)
{
    if (r->hThread != NULL)
    {
        TerminateThread (r->hThread, 0);
        CloseHandle (r->hThread);
    }

    return 0;
}

DWORD RandomizerRun(Randomizer* r, RProc proc)
{
    DWORD dwId;
    r->hThread = CreateThread (NULL,
                 NULL,
                 proc,
                 r->a,
                 0,
                 &dwId);
    r->dwThreadId = dwId;
    return 0;
}

/*WINAPI DWORD RandomizerUpdate (LPVOID lpvVar)
{

    while (1)
    {
        int a = (rand () % (255*2 + 1)) - 255;
        *((int*)lpvVar) = a;
    }

    return 0;
}*/
