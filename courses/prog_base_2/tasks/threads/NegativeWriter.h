#ifndef NEGATIVEWRITER_H_INCLUDED
#define NEGATIVEWRITER_H_INCLUDED

#include <windows.h>

typedef struct tagNegativeWriterPrivate NegativeWriterPrivate;

typedef struct
{
    NegativeWriterPrivate* nwp;
} NegativeWriter;

int NegativeWriterInitialize (NegativeWriter* , int* );
int NegativeWriterDeinitialize (NegativeWriter* );

int NegativeWriterRun (NegativeWriter*);
int NegativeWriterSetMutex (NegativeWriter*, HANDLE);

static WINAPI NegativeWriterWrite (LPVOID);

#endif // NEGATIVEWRITER_H_INCLUDED
