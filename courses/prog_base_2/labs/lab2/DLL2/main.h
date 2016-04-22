#ifndef __MAIN_H__
#define __MAIN_H__


/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "stack.h"

void DLL_EXPORT addString(Stack* s);
void DLL_EXPORT stackFullReaction (Stack* s);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
