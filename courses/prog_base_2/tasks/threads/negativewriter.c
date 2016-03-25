#include "negativewriter.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int NegativeWriterInitialize (NegativeWriter* nw, int* a)
{
    nw->a = a;

    return 0;
}

int NegativeWriterDeinitialize (NegativeWriter* nw)
{
    if (nw->hThread != NULL)
    {
        TerminateThread (nw->hThread, 0);
        CloseHandle (nw->hThread);
    }

    return 0;
}

int NegativeWriterRun (NegativeWriter* nw, WProc proc)
{
    DWORD dwId;
    nw->hThread = CreateThread (NULL,
                 NULL,
                 proc,
                 nw->a,
                 0,
                 &dwId);
    nw->dwThreadId = dwId;
    return 0;
}

/*static WINAPI NegativeWriterWrite (LPVOID lpvVar)
{
    while (1)
    {
        int a = *((int*)lpvVar);
        if (a < 0)
            printf ("%d\n", a);
    }
}*/
