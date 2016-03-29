#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED

#include <windows.h>

typedef struct tagRandomizerPrivate RandomizerPrivate;

typedef struct
{
    RandomizerPrivate* rp;
} Randomizer;

int RandomizerInitialize (Randomizer*, int* );
int RandomizerDeinitialize (Randomizer*);
DWORD RandomizerRun (Randomizer*);
int RandomizerSetMutex (Randomizer*, HANDLE);

static DWORD WINAPI RandomizerUpdate(LPVOID);

#endif // RANDOMIZER_H_INCLUDED
