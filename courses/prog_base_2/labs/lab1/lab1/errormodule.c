#include "errormodule.h"

int ErrorModule_setLastError (int c)
{
    iErrorCode = c;

    return 0;
}
int ErrorModule_getLastError ()
{
    return iErrorCode;
}
