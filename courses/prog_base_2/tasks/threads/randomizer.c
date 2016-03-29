#include "randomizer.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct tagRandomizerPrivate
{
    int* a;
    HANDLE hThread;
    HANDLE hMutex;
    DWORD dwThreadId;
};

typedef struct
{
    HANDLE hMutex;
    int* a;
} ThreadData, *LPThreadData;

int RandomizerInitialize(Randomizer* r, int* a)
{
    srand (time (NULL));
    RandomizerPrivate* rp = malloc (sizeof(RandomizerPrivate));
    ZeroMemory (rp, sizeof (RandomizerPrivate));
    rp->a = a;
    r->rp = rp;

    return 0;
}

int RandomizerDeinitialize (Randomizer* r)
{
    if (r->rp->hThread != NULL)
    {
        TerminateThread (r->rp->hThread, 0);
        CloseHandle (r->rp->hThread);
    }
    free (r->rp);

    return 0;
}

int RandomizerSetMutex (Randomizer* r, HANDLE hMutex)
{
    r->rp->hMutex = hMutex;

    return 0;
}

DWORD RandomizerRun (Randomizer* r)
{
    DWORD dwId;
    ThreadData td;
    td.a = r->rp->a;
    td.hMutex = r->rp->hMutex;
    r->rp->hThread = CreateThread (NULL,
                                     NULL,
                                     RandomizerUpdate,
                                     &td,
                                     0,
                                     &dwId);
    r->rp->dwThreadId = dwId;
    return 0;
}

static WINAPI DWORD RandomizerUpdate (LPVOID lpvVar)
{
    HANDLE hMutex = ((LPThreadData)lpvVar)->hMutex;
    int* a = ((LPThreadData)lpvVar)->a;
    while (1)
    {
        if (hMutex != NULL )
            WaitForSingleObject(hMutex, INFINITE);

        int r = (rand () % (255*2 + 1)) - 255;
        *a = r;

        if (hMutex != NULL)
            ReleaseMutex (hMutex);
    }

    return 0;
}
