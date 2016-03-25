#ifndef NEGATIVEWRITER_H_INCLUDED
#define NEGATIVEWRITER_H_INCLUDED

#include <windows.h>

typedef DWORD (WINAPI *WProc)(LPVOID);

typedef struct
{
    int* a;
    HANDLE hThread;
    DWORD dwThreadId;
} NegativeWriter;

int NegativeWriterInitialize (NegativeWriter* , int* );
int NegativeWriterDeinitialize (NegativeWriter* );

int NegativeWriterRun (NegativeWriter* , WProc);

//static WINAPI NegativeWriterWrite (LPVOID);

#endif // NEGATIVEWRITER_H_INCLUDED
