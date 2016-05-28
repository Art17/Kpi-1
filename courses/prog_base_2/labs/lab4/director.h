#ifndef DIRECTOR_H_INCLUDED
#define DIRECTOR_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct director_s* director_t;

director_t director_new ();

void director_fromXmlNode (director_t, xmlDocPtr, xmlNodePtr);
void director_toXmlNode (director_t, xmlDocPtr, xmlNodePtr);

void director_setValue (director_t, const char*, void*);
void director_getValue (director_t, const char*, void*);

char director_getInfo (director_t, char []);

void director_free (director_t);

#endif // DIRECTOR_H_INCLUDED
