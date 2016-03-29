#include "negativewriter.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct
{
    int* a;
    HANDLE hMutex;
} ThreadData, *LPThreadData;

struct tagNegativeWriterPrivate
{
    int* a;
    HANDLE hThread;
    HANDLE hMutex;
    DWORD dwThreadId;
};

int NegativeWriterInitialize (NegativeWriter* nw, int* a)
{
    NegativeWriterPrivate* nwp = malloc (sizeof (NegativeWriterPrivate));
    ZeroMemory (nwp, sizeof (NegativeWriterPrivate));
    nwp->a = a;
    nw->nwp = nwp;

    return 0;
}

int NegativeWriterDeinitialize (NegativeWriter* nw)
{
    if (nw->nwp->hThread != NULL)
    {
        TerminateThread (nw->nwp->hThread, 0);
        CloseHandle (nw->nwp->hThread);
    }

    free (nw->nwp);

    return 0;
}

int NegativeWriterRun (NegativeWriter* nw)
{
    ThreadData td;

    td.a = nw->nwp->a;
    td.hMutex = nw->nwp->hMutex;

    DWORD dwId;
    nw->nwp->hThread = CreateThread (NULL,
                     NULL,
                     NegativeWriterWrite,
                     &td,
                     0,
                     &dwId);
    nw->nwp->dwThreadId = dwId;
    return 0;
}

int NegativeWriterSetMutex (NegativeWriter* nw, HANDLE hMutex)
{
    nw->nwp->hMutex = hMutex;

    return 0;
}

static WINAPI NegativeWriterWrite (LPVOID lpvVar)
{
    HANDLE hMutex = ((LPThreadData)lpvVar)->hMutex;
    int* a = ((LPThreadData)lpvVar)->a;
    while (1)
    {
        if (hMutex != NULL)
            WaitForSingleObject (hMutex, INFINITE);
        if (*a < 0)
            printf ("%d\n", *a);
        if (hMutex != NULL)
            ReleaseMutex (hMutex);
    }
}
