#include "director.h"

struct director_s
{
    char name[16];
    char surname[16];
    char birthdate[16];

    double budget;
    int years;
};

director_t director_new ()
{
    director_t self = malloc ( sizeof (struct director_s) );
    memset (self, 0, sizeof (struct director_s));

    return self;
}

void director_fromXmlNode (director_t self, xmlDocPtr doc, xmlNodePtr directorNode)
{
    for (xmlNodePtr currentNode = directorNode->xmlChildrenNode; currentNode != NULL; currentNode = currentNode->next)
    {
        if (xmlStrcmp( currentNode->name, "name" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->name,  buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "surname" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->surname, buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "birthdate" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(self->birthdate, buffer);
            free(buffer);
        }
        else if (xmlStrcmp( currentNode->name, "budget" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            double budget = strtod (buffer, NULL);
            self->budget = budget;
            free(buffer);
        }
        else if (xmlStrcmp( currentNode->name, "years" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            int years = atoi (buffer);
            self->years = years;
            free(buffer);
        }
    }
}

void director_toXmlNode(director_t self, xmlDocPtr doc, xmlNodePtr parentNode)
{
    char buffer [256];
    xmlNodePtr directorNode = NULL;

    if ( parentNode != NULL )
        directorNode = xmlNewChild (parentNode, NULL, "director", NULL);
    else
    {
        directorNode = xmlNewNode (NULL, "director");
        xmlDocSetRootElement (doc, directorNode);
    }

    xmlNewChild(directorNode, NULL, "name", self->name);
    xmlNewChild(directorNode, NULL, "surname", self->surname);
    xmlNewChild(directorNode, NULL, "birthdate", self->birthdate);

    sprintf(buffer, "%f", self->budget);
    xmlNewChild(directorNode, NULL, "budget", buffer);

    sprintf(buffer, "%d", self->years);
    xmlNewChild(directorNode, NULL, "years", buffer);
}

void director_setValue (director_t self, const char* key, void* value)
{
    if ( strcmp (key, "name") == 0 )
    {
        strcpy (self->name, value);
    }
    else if ( strcmp (key, "surname") == 0 )
    {
        strcpy (self->surname, value);
    }
    else if ( strcmp (key, "birthdate") == 0 )
    {
        strcpy (self->birthdate, value);
    }
    else if ( strcmp ( key, "budget" ) == 0 )
    {
        self->budget = *((double*)value);
    }
    else if ( strcmp ( key, "years" ) == 0 )
    {
        self->years = *((int*)value);
    }
}
void director_getValue (director_t self, const char* key, void* value)
{
    if ( strcmp (key, "name") == 0 )
    {
        strcpy (value, self->name);
    }
    else if ( strcmp (key, "surname") == 0 )
    {
        strcpy (value, self->surname);
    }
    else if ( strcmp (key, "birthdate") == 0 )
    {
        strcpy (value, self->birthdate);
    }
    else if ( strcmp ( key, "budget" ) == 0 )
    {
        *((double*)value) = self->budget;
    }
    else if ( strcmp ( key, "years" ) == 0 )
    {
        *((int*)value) = self->years;
    }
}

char director_getInfo (director_t self, char buffer [])
{
    char info [256];
    sprintf (info, "%s %s has %f dollars and %d years experience", self->name, self->surname, self->budget, self->years);

    strcpy (buffer, info);

    return buffer;
}

void director_free (director_t self)
{
    free (self);
}
