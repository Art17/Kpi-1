#include "data_manager.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

struct data_manager_s
{
    list_t directors;
};

const char* szSourcePath = "data/directors.xml";

data_manager_t data_manager_new ()
{
    data_manager_t self = malloc ( sizeof (struct data_manager_s) );
    memset (self, 0, sizeof ( struct data_manager_s) );

    self->directors = list_new();

    return self;
}

void data_manager_load (data_manager_t self)
{
    xmlDocPtr doc = xmlParseFile (szSourcePath);
    xmlNodePtr rootElement = xmlDocGetRootElement(doc);

    int i = 0;
    for (xmlNodePtr currentNode = rootElement->xmlChildrenNode;
        currentNode != NULL;
        currentNode = currentNode->next )
        if (xmlStrcmp(currentNode->name, "director") == 0)
        {
            director_t dir = director_new ();
            list_append(self->directors, dir);

            director_fromXmlNode (dir, doc, currentNode);
        }

    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void data_manager_save (data_manager_t self)
{
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    doc = xmlNewDoc ("1.0");
    root_element = xmlNewNode (NULL, "directors");
    xmlDocSetRootElement (doc, root_element);

    int qDirs = list_getSize(self->directors);

    for (int i = 0; i < qDirs; i++)
    {
        director_toXmlNode (list_get (self->directors, i, NULL), doc, root_element);
    }

    xmlSaveFormatFileEnc (szSourcePath, doc, "UTF-8", 1);
    xmlFreeDoc (doc);
}

char* data_manager_getAsString (data_manager_t self, char buffer[], int id)
{
    xmlDoc* doc = NULL;
    xmlNode* root_element = NULL;

    doc = xmlNewDoc ("1.0");
    root_element = xmlNewNode (NULL, "directors");
    xmlDocSetRootElement (doc, root_element);

    int qDirs = list_getSize(self->directors);

    for (int i = 0; i < qDirs; i++)
    {
        if (id == i || id == -1)
            director_toXmlNode (list_get (self->directors, i, NULL), doc, root_element);
    }

    xmlChar* pMem = NULL;
    int size = 0;
    xmlDocDumpMemory(doc, &pMem, &size);

	strcpy(buffer, pMem);

    free(pMem);
    xmlFreeDoc (doc);

    return buffer;
}


void data_manager_add (data_manager_t self, director_t director)
{
    list_append (self->directors, director);
}

void data_manager_delete(data_manager_t self, int index)
{
    list_remove(self->directors, index, NULL);
}

int data_manager_getSize (data_manager_t self)
{
    return list_getSize( self->directors );
}

director_t data_manager_get (data_manager_t self, int index)
{
    return list_get (self->directors, index, NULL);
}

void data_manager_free (data_manager_t self)
{
    list_free(self->directors);

    free (self);
}
