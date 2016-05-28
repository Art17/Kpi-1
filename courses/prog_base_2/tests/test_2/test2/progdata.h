#ifndef PROGDATA_H_INCLUDED
#define PROGDATA_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <time.h>

typedef struct progdata_s* progdata_t;

progdata_t progdata_new ();

void progdata_fromXmlNode (progdata_t, xmlDocPtr, xmlNodePtr);
void progdata_toXmlNode (progdata_t, xmlDocPtr, xmlNodePtr);

void progdata_setValue (progdata_t, const char*, void*);
void progdata_getValue (progdata_t, const char*, void*);

char* progdata_getValues (progdata_t, char []);
void progdata_setValues (progdata_t, const char*);

void progdata_fromMemory (progdata_t, const char* , int);

void progdata_getAsString (progdata_t, char []);

void progdata_free (progdata_t);

#endif // PROGDATA_H_INCLUDED
