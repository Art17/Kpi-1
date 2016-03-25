#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include <windows.h>

typedef DWORD (WINAPI *RProc)(LPVOID);

typedef struct
{
    int* a;
    HANDLE hThread;
    DWORD dwThreadId;
} Randomizer;

int RandomizerInitialize (Randomizer*, int* );
int RandomizerDeinitialize (Randomizer*);
DWORD RandomizerRun (Randomizer* , RProc);

//static DWORD WINAPI RandomizerUpdate (LPVOID);

#endif // RANDOMIZER_H_INCLUDED
