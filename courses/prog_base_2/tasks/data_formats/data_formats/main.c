#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "director.h"

int main ()
{
    const char* szFilePath = "files//director.xml";
    const int DirNum = 3;
    Director directors[DirNum];

    xmlDocPtr doc = xmlParseFile (szFilePath);
    xmlNodePtr rootElement = xmlDocGetRootElement(doc);

    int i = 0;
    for (xmlNodePtr currentNode = rootElement->xmlChildrenNode;
        currentNode != NULL && i < DirNum;
        currentNode = currentNode->next )
        if (xmlStrcmp(currentNode->name, "director") == 0)
            DirectorInitialize (&directors[i++], doc, currentNode);

    for (int i = 0; i < DirNum; i++)
        DirectorPrintData(&directors[i]);

    for (int i = 0; i < DirNum; i++)
        DirectorDeinitialize (&directors[i]);

    xmlFreeDoc(doc);
    xmlCleanupParser();


    return 0;
}
