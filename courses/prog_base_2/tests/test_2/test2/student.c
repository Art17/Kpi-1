#include "student.h"

struct student_s
{
    char name[16];
    char surname[16];
    int var;
};

student_t student_new ()
{
    student_t self = malloc ( sizeof (struct student_s) );
    memset (self, 0, sizeof (struct student_s));

    return self;
}

void student_fromXmlNode (student_t self, xmlDocPtr doc, xmlNodePtr studentNode)
{
    for (xmlNodePtr currentNode = studentNode->xmlChildrenNode; currentNode != NULL; currentNode = currentNode->next)
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
        else if (xmlStrcmp( currentNode->name, "var" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            int var = atoi (buffer);
            self->var = var;
            free(buffer);
        }
    }
}

void student_toXmlNode(student_t self, xmlDocPtr doc, xmlNodePtr parentNode)
{
    char buffer [256];
    xmlNodePtr studentNode = NULL;

    if ( parentNode != NULL )
        studentNode = xmlNewChild (parentNode, NULL, "student", NULL);
    else
    {
        studentNode = xmlNewNode (NULL, "student");
        xmlDocSetRootElement (doc, studentNode);
    }

    xmlNewChild(studentNode, NULL, "name", self->name);
    xmlNewChild(studentNode, NULL, "surname", self->surname);

    sprintf(buffer, "%d", self->var);
    xmlNewChild(studentNode, NULL, "var", buffer);
}

void student_setValue (student_t self, const char* key, void* value)
{
    if ( strcmp (key, "name") == 0 )
    {
        strcpy (self->name, value);
    }
    else if ( strcmp (key, "surname") == 0 )
    {
        strcpy (self->surname, value);
    }
    else if ( strcmp ( key, "var" ) == 0 )
    {
        self->var = *((int*)value);
    }
}

void student_setValues (student_t self, const char* params)
{
    char name[24];
    char surname[24];
    int var;

    sscanf (params, "%s %s %d", name, surname, &var);

    student_setValue(self, "name", name);
    student_setValue(self, "surname", surname);
    student_setValue(self, "var", &var);
}

void student_getValue (student_t self, const char* key, void* value)
{
    if ( strcmp (key, "name") == 0 )
    {
        strcpy (value, self->name);
    }
    else if ( strcmp (key, "surname") == 0 )
    {
        strcpy (value, self->surname);
    }
    else if ( strcmp ( key, "var" ) == 0 )
    {
        *((int*)value) = self->var;
    }
}

char* student_getValues (student_t self, char buffer[])
{
    sprintf (buffer, "%s %s %d", self->name,
             self->surname,
             self->var );
    return buffer;
}

void student_free (student_t self)
{
    free (self);
}
