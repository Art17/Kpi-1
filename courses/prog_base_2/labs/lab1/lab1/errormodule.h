#ifndef ERRORMODULE_H_INCLUDED
#define ERRORMODULE_H_INCLUDED

static int iErrorCode = 0;

int ErrorModule_setLastError (int);
int ErrorModule_getLastError ();

#endif // ERRORMODULE_H_INCLUDED
