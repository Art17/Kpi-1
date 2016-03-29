#include <stdio.h>
#include <stdlib.h>
#include "randomizer.h"
#include "negativewriter.h"
#include <windows.h>

void main_loop ()
{
    while (1)
    {

    }
}

int main()
{
    HANDLE hMutex = CreateMutex (
                                  NULL,
                                  FALSE,
                                  NULL);

    int a = 0;
    Randomizer r1, r2;
    NegativeWriter nw1, nw2;

    RandomizerInitialize (&r1, &a);
    RandomizerInitialize (&r2, &a);

    RandomizerSetMutex (&r1, hMutex);
    RandomizerSetMutex (&r2, hMutex);

    NegativeWriterInitialize (&nw1, &a);
    NegativeWriterInitialize (&nw2, &a);

    NegativeWriterSetMutex(&nw1, hMutex);
    NegativeWriterSetMutex(&nw2, hMutex);

    RandomizerRun (&r1);
    RandomizerRun (&r2);

    NegativeWriterRun (&nw1);
    NegativeWriterRun (&nw2);

    main_loop ();

    RandomizerDeinitialize (&r1);
    RandomizerDeinitialize (&r2);

    NegativeWriterDeinitialize (&nw1);
    NegativeWriterDeinitialize (&nw2);

    CloseHandle (hMutex);

    return 0;
}
