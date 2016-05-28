#include "progdata.h"

struct progdata_s
{
    char author [256];
    char quote [256];
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

        else if (xmlStrcmp( currentNode->name, "quote" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->quote, buffer);
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
    xmlNewChild(progdataNode, NULL, "quote", self->quote);
    xmlNewChild(progdataNode, NULL, "time", self->time);
}

void progdata_setValue (progdata_t self, const char* key, void* value)
{
    if ( strcmp (key, "author") == 0 )
    {
        strcpy (self->author, value);
    }
    else if ( strcmp (key, "quote") == 0 )
    {
        strcpy (self->quote, value);
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
        strcpy (value, self->quote);
    }
    else if ( strcmp ( key, "time" ) == 0 )
    {
        strcpy (value, self->time);
    }
}

char* progdata_getValues (progdata_t self, char buffer[])
{
    sprintf (buffer, "%s %s %s", self->author,
             self->quote,
             self->time );
    return buffer;
}

void progdata_free (progdata_t self)
{
    free (self);
}
