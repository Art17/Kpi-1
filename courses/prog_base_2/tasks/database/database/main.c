#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sqldatabase.h"
#include "record.h"

int main()
{
    srand (time (NULL));

    const char* szFilePath = "data\\director.db";
    const char* szTableName = "Director";
    SqlDatabase sqlDatabase;

    SqlDatabaseInitialize (&sqlDatabase);
    int ret = SqlDatabaseSetDbFile (&sqlDatabase, szFilePath, szTableName);
    if (SQLITE_OK != ret)
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }

    int qRows = SqlDatabaseGetRowsQuantity (&sqlDatabase);

    if (qRows == -1)
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }

    printf ("Rows quantity: %d\n", qRows);

    printf ("printing all database: \n\n");
    printf ("---------------------------------------\n\n");
    if (SQLITE_ERROR == SqlDatabasePrintAll (&sqlDatabase))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("---------------------------------------\n\n");

    double K = 5.0;
    int P = 100;
    printf ("print all directos budget > %f and years < %d\n", K, P);
    printf ("---------------------------------------\n\n");
    if (SQLITE_ERROR == SqlDatabaseTask (&sqlDatabase, K, P))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("---------------------------------------\n\n");


    int row = 8;
    printf ("printing %d row\n", row);
    printf ("-------------------------------\n");
    if (SQLITE_ERROR == SqlDatabasePrintById(&sqlDatabase, row))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("-------------------------------\n");


    printf ("Deleting 3 element\n\n");
    SqlDatabaseDeleteRecordById (&sqlDatabase, 3);
    printf ("printing all database: \n\n");
    printf ("---------------------------------------\n\n");
    if (SQLITE_ERROR == SqlDatabasePrintAll (&sqlDatabase))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("---------------------------------------\n\n");

    int id = 3;
    Record rec;
    const char* names[] = {"Jack", "Bob", "Clark", "Jackson", "Piter", "Adam", "Pol", "Aaron", "Mike"};
    int qNames = sizeof (names) / sizeof (char*);
    rec.id = id;
    strcpy (rec.name, names[ rand () % qNames ]);
    strcpy (rec.surname, "Parker");
    strcpy (rec.birthdate, "1991-02-02");
    rec.budget = 125.25;
    rec.years = 40;

    printf ("creating new record with %d id\n", id);
    SqlDatabaseCreateRecord(&sqlDatabase, &rec);
    printf ("printing all database: \n\n");
    printf ("---------------------------------------\n\n");
    if (SQLITE_ERROR == SqlDatabasePrintAll (&sqlDatabase))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("---------------------------------------\n\n");

    printf ("update Director. set budget = 5000 where years >= 50\n");
    SqlDatabaseUpdate (&sqlDatabase, 5000., 50);
    printf ("printing all database: \n\n");
    printf ("---------------------------------------\n\n");
    if (SQLITE_ERROR == SqlDatabasePrintAll (&sqlDatabase))
    {
        SqlDatabaseDeinitialize (&sqlDatabase);
        return 0;
    }
    printf ("---------------------------------------\n\n");

    SqlDatabaseDeinitialize (&sqlDatabase);
    return 0;
}
