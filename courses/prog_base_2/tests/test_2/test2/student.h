#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>

typedef struct student_s* student_t;

student_t student_new ();

void student_fromXmlNode (student_t, xmlDocPtr, xmlNodePtr);
void student_toXmlNode (student_t, xmlDocPtr, xmlNodePtr);

void student_setValue (student_t, const char*, void*);
void student_getValue (student_t, const char*, void*);

char* student_getValues (student_t, char []);
void student_setValues (student_t, const char*);

char student_getInfo (student_t, char []);

void student_free (student_t);

#endif // DIRECTOR_H_INCLUDED
