#include "director.h"

struct tagDirector_Private
{
    char name[24];
    char surname[24];
    char birthdate[12];
    int year;
    double magic;
};


int DirectorInitialize(Director* director, xmlDocPtr doc, xmlNodePtr directorNode)
{
    director->dp = malloc (sizeof(Director_Private));
    memset (director->dp, 0, sizeof(Director_Private));

    for (xmlNodePtr currentNode = directorNode->xmlChildrenNode; currentNode != NULL; currentNode = currentNode->next)
    {
        if (xmlStrcmp( currentNode->name, "name" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(director->dp->name,  buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "surname" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(director->dp->surname, (const char *) buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "birthdate" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            strcpy(director->dp->birthdate, buffer);
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "year" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            int year = atoi (buffer);
            director->dp->year = year;
            free(buffer);
        }

        else if (xmlStrcmp( currentNode->name, "magic" ) == 0)
        {
            xmlChar * buffer = xmlNodeListGetString(doc, currentNode->xmlChildrenNode, 1);
            double magic = strtod (buffer, NULL);
            director->dp->magic = magic;
            free(buffer);
        }
    }

    return 0;
}

int DirectorDeinitialize (Director* director)
{
    free (director->dp);

    return 0;
}

int DirectorPrintData (Director* director)
{
    printf ("name:      \t%s\n", director->dp->name);
    printf ("surname:   \t%s\n", director->dp->surname);
    printf ("birthdate: \t%s\n", director->dp->birthdate);
    printf ("year:      \t%d\n", director->dp->year);
    printf ("magic:     \t%.2f\n", director->dp->magic);

    printf ("\n");

    return 0;
}
