#ifndef DIRECTOR_H_INCLUDED
#define DIRECTOR_H_INCLUDED

#include <stdio.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct tagDirector_Private Director_Private;

typedef struct
{
    Director_Private* dp;
} Director;

int DirectorInitialize (Director*, xmlDocPtr, xmlNodePtr);
int DirectorPrintData (Director*);
int DirectorDeinitialize (Director*);

#endif // DIRECTOR_H_INCLUDED
