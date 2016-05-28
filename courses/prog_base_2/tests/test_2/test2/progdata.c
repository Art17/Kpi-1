#include "progdata.h"

struct progdata_s
{
    char author [256];
    char book [256];
    char time [12];
};

progdata_t progdata_new ()
{
    progdata_t self = malloc ( sizeof (struct progdata_s) );
    memset (self, 0, sizeof (struct progdata_s));

    return self;
}

void progdata_fromXmlNode (progdata_t self, xmlDocPtr doc, xmlNodePtr progdataNode)
{
    for (xmlNodePtr currentNode = progdataNode->xmlChildrenNode; currentNode != NULL; currentNode = currentNode->next)
    {
        if (xmlStrcmp( currentNode->name, "author" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->author,  buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "book" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->book, buffer);
            free(buffer);
        }
    }

  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strcpy (self->time, asctime (timeinfo));
}

void progdata_toXmlNode(progdata_t self, xmlDocPtr doc, xmlNodePtr parentNode)
{
    char buffer [256];
    xmlNodePtr progdataNode = NULL;

    if ( parentNode != NULL )
        progdataNode = xmlNewChild (parentNode, NULL, "progdata", NULL);
    else
    {
        progdataNode = xmlNewNode (NULL, "progdata");
        xmlDocSetRootElement (doc, progdataNode);
    }

    xmlNewChild(progdataNode, NULL, "author", self->author);
    xmlNewChild(progdataNode, NULL, "book", self->book);
    xmlNewChild(progdataNode, NULL, "time", self->time);
}

void progdata_fromMemory (progdata_t self, const char* memory, int size)
{
    xmlDocPtr doc = xmlReadMemory (memory, size, NULL, NULL, NULL);
    xmlNodePtr rootElement = xmlDocGetRootElement(doc);

    progdata_fromXmlNode (self, doc, rootElement);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void progdata_getAsString (progdata_t self, char buffer[])
{
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    doc = xmlNewDoc ("1.0");
    root_element = xmlNewNode (NULL, "data");
    xmlDocSetRootElement (doc, root_element);

    progdata_toXmlNode (self, doc, root_element);

    xmlChar* pMem = NULL;
    int size = 0;
    xmlDocDumpMemory(doc, &pMem, &size);

    strcpy (buffer, pMem);

    free(pMem);
    xmlFreeDoc (doc);

    return buffer;
}

void progdata_setValue (progdata_t self, const char* key, void* value)
{
    if ( strcmp (key, "author") == 0 )
    {
        strcpy (self->author, value);
    }
    else if ( strcmp (key, "book") == 0 )
    {
        strcpy (self->book, value);
    }
    else if ( strcmp ( key, "time" ) == 0 )
    {
        strcpy (self->time, value);
    }
}

void progdata_setValues (progdata_t self, const char* params)
{
    char name[24];
    char surname[24];
    char time [24];

    sscanf (params, "%s %s %s", name, surname, time);

    progdata_setValue(self, "name", name);
    progdata_setValue(self, "surname", surname);
    progdata_setValue(self, "time", time);
}

void progdata_getValue (progdata_t self, const char* key, void* value)
{
    if ( strcmp (key, "name") == 0 )
    {
        strcpy (value, self->author);
    }
    else if ( strcmp (key, "surname") == 0 )
    {
        strcpy (value, self->book);
    }
    else if ( strcmp ( key, "time" ) == 0 )
    {
        strcpy (value, self->time);
    }
}

char* progdata_getValues (progdata_t self, char buffer[])
{
    sprintf (buffer, "%s %s %s", self->author,
             self->book,
             self->time );
    return buffer;
}

void progdata_free (progdata_t self)
{
    free (self);
}
