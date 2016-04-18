#ifndef SQLDB_H_INCLUDED
#define SQLDB_H_INCLUDED

#include <sqlite3.h>
#include "record.h"

typedef struct tagSqlDatabase_Private SqlDatabase_Private;

typedef struct
{
    SqlDatabase_Private* sp;
} SqlDatabase;

void SqlDatabaseInitialize (SqlDatabase* );
int  SqlDatabaseSetDbFile (SqlDatabase*, const char*, const char*);
int  SqlDatabaseGetRowsQuantity (SqlDatabase*);
int  SqlDatabasePrintAll (SqlDatabase*);
int  SqlDatabaseDeleteRecordById (SqlDatabase*, int);
int  SqlDatabaseTask (SqlDatabase*, double, int);
int  SqlDatabasePrintById (SqlDatabase*, int);
int  SqlDatabaseCreateRecord (SqlDatabase*, const Record*);
void SqlDatabaseDeinitialize (SqlDatabase* );

#endif // SQLDB_H_INCLUDED
