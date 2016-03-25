#include <stdio.h>
#include <stdlib.h>
#include "randomizer.h"
#include "negativewriter.h"
#include <windows.h>

HANDLE hMutex;

DWORD WINAPI MyRandomizerProc (LPVOID lpvVar)
{
    while (1)
    {
        WaitForSingleObject(hMutex, INFINITE);
        int a = (rand () % (255*2 + 1)) - 255;
        *((int*)lpvVar) = a;
        ReleaseMutex (hMutex);
    }

    return 0;
}

DWORD WINAPI MyWriterProc (LPVOID lpvVar)
{
    while (1)
    {
        WaitForSingleObject(hMutex, INFINITE);
        int a = *((int*)lpvVar);
        if (a < 0)
            printf ("%d\n", a);
        ReleaseMutex (hMutex);
    }

    return 0;
}

int main()
{
    hMutex = CreateMutex (
                          NULL,
                          FALSE,
                          NULL);

    int a = 0;
    Randomizer r1, r2;
    NegativeWriter nw1, nw2;

    RandomizerInitialize (&r1, &a);
    RandomizerInitialize (&r2, &a);

    NegativeWriterInitialize (&nw1, &a);
    NegativeWriterInitialize (&nw2, &a);

    RandomizerRun (&r1, MyRandomizerProc);
    RandomizerRun (&r2, MyRandomizerProc);

    NegativeWriterRun (&nw1, MyWriterProc);
    NegativeWriterRun (&nw2, MyWriterProc);

    while (1)
    {
    }

    RandomizerDeinitialize (&r1);
    RandomizerDeinitialize (&r2);

    NegativeWriterDeinitialize (&nw1);
    NegativeWriterDeinitialize (&nw2);

    CloseHandle (hMutex);

    return 0;
}
