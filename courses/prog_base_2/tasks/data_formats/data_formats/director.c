#include "director.h"

typedef struct tagCompany
{
    char country[24];
    char name[24];
} Company;

struct tagDirector_Private
{
    char name[24];
    char surname[24];
    char birthdate[12];
    int year;
    double magic;
    Company company;
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
        else if (xmlStrcmp (currentNode->name, "company") == 0)
        {
            char* country = xmlGetProp (currentNode, "country");
            strcpy (director->dp->company.country, country);
            for (xmlNodePtr currentNode2 = currentNode->xmlChildrenNode;
                    currentNode2 != NULL;
                    currentNode2 = currentNode2->next)
            {
                if (xmlStrcmp(currentNode2->name, "name") == 0)
                {
                    char* buffer = xmlNodeListGetString(doc, currentNode2->xmlChildrenNode, 1);
                    strcpy (director->dp->company.name, buffer);
                    free (buffer);
                }
            }
            free (country);
        }
        /*else if (!xmlStrcmp(cur->name, (const xmlChar *)"corporation")) {
            xmlChar * country = xmlGetProp(cur, "country");
            for(xmlNodePtr cur1 = cur->xmlChildrenNode; cur1 != NULL; cur1 = cur1->next){
                if(!xmlStrcmp(cur1->name, (const xmlChar *)"name")){
                    xmlChar * name = xmlNodeListGetString(doc, cur1->xmlChildrenNode, 1);
                    strcpy(self->corporationData.name, (const char *) name);
                    free(name);
                }
            }
            strcpy(self->corporationData.country, (const char *) country);
            free(country);*/
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

    printf ("company: \n");
    printf ("\tcountry: %s\n", director->dp->company.country);
    printf ("\tname: %s\n", director->dp->company.name);

    printf ("\n");

    return 0;
}
