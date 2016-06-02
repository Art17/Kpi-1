#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sqldatabase.h"
#include "record.h"


 const char* names [] =
		{
			"Aaron",
			"Austin",
			"Blake",
			"Carl",
			"Charles",
			"Daniel",
			"David",
			"Dominic",
			"Elbert",
			"Emrick",
			"Gabriel",
			"Gale",
			"Hunter",
			"Jack",
			"Jacob",
		};
	const char* snames [] =
		{
			"Smith",
			"Williams",
			"Miller",
			"Anderson",
			"Thomas",
			"White",
			"Clark",
			"Lewis",
			"Lee",
			"Roberts",
			"Parker",
			"Butler",
			"Russell",
			"Griffin",
			"Diaz",
		};

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

    char date [15];

    sprintf (date, "%04d-%02d-%02d", rand () % 40 + 1960, rand () % 12 + 1, rand () % 29 + 1);

    int qNames = sizeof (names) / sizeof (char*);
    int qSNames = sizeof (snames) / sizeof (char*);
    rec.id = id;
    strcpy (rec.name, names[ rand () % qNames ]);
    strcpy (rec.surname, snames [ rand () %qSNames ]);
    strcpy (rec.birthdate, "1991-02-02");
    rec.budget = (double)(rand () % 200 + 100) / 10;
    rec.years = rand () % 100 + 50;

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

    sprintf (date, "%04d-%02d-%02d", rand () % 40 + 1960, rand () % 12 + 1, rand () % 29 + 1);

    rec.id = 1;
    strcpy (rec.name, names[ rand () % qNames ]);
    strcpy (rec.surname, "Johnson");
    strcpy (rec.birthdate, date);
    rec.budget = rand () % 200 / 10;
    rec.years = rand () % 100 + 50;

    printf ("update first record\n");
    SqlDatabaseUpdate (&sqlDatabase, &rec);
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
