#include "sqldatabase.h"
#include <stdio.h>

#define TEST_VERSION 1

struct tagSqlDatabase_Private
{
    char szTableName [36];
    char szDbFilePath [256];
    sqlite3* db;
};

static int printTable (sqlite3_stmt** stmt)
{
    int ret = SQLITE_OK;
    while (1) {
        ret = sqlite3_step(*stmt);
        if (SQLITE_ERROR == ret)
        {
            #ifdef TEST_VERSION
            printf ("Error printing table\n");
            #endif // TEST_VERSION
            return ret;
        }
        else if (SQLITE_DONE == ret)
        {  // we reached the end of the table
            break;
        }
        else if (SQLITE_ROW == ret){
            // process current row
            int count = sqlite3_column_count(*stmt);  // get number of values in row
            for (int i = 0; i < count; i++) {  // iterate values in row
                const char * colName = sqlite3_column_name(*stmt, i);
                //const char * colType = sqlite3_column_decltype(*stmt, i);
                const char * value = sqlite3_column_text(*stmt, i);
                //printf("%10s [%7s] = %s\n", colName, colType, value);
                printf("%10s = %s\n", colName, value);
            }
            printf("\n");
        }
    }

    return ret;
}

void SqlDatabaseInitialize (SqlDatabase* pSqlDatabase)
{
    pSqlDatabase->sp = malloc ( sizeof (SqlDatabase_Private) );
    memset (pSqlDatabase->sp, 0, sizeof (SqlDatabase_Private));
}

void SqlDatabaseDeinitialize (SqlDatabase* pSqlDatabase)
{
    sqlite3_close(pSqlDatabase->sp->db);
    free ( pSqlDatabase->sp );
}

int SqlDatabaseSetDbFile (SqlDatabase* pSqlDatabase, const char* szDbFilePath, const char* szTableName)
{
    int ret = sqlite3_open (szDbFilePath, &pSqlDatabase->sp->db);

    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error opening database file\n");
        #endif // TEST_VERSION
        return ret;
    }

    strcpy (pSqlDatabase->sp->szDbFilePath, szDbFilePath);
    strcpy (pSqlDatabase->sp->szTableName, szTableName);

    return ret;
}

int SqlDatabaseGetRowsQuantity (SqlDatabase* pSqlDatabase)
{
    const char* szSqlStatement = "SELECT COUNT(*) FROM Director"; // You can't pass the table name as a parameter.
    sqlite3_stmt* stmt = NULL;

    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return -1;
    }

    ret = sqlite3_step(stmt);

    if (SQLITE_ROW != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error making step\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return -1;
    }

    ret = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    return ret;
}

int SqlDatabasePrintAll (SqlDatabase* pSqlDatabase)
{
    const char* szSqlStatement = "SELECT * FROM Director"; // You can't pass the table name as a parameter.
    sqlite3_stmt* stmt = NULL;

    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statementn");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    return printTable (&stmt);
}

int SqlDatabaseDeleteRecordById (SqlDatabase* pSqlDatabase, int id)
{
    const char* szSqlStatement = "DELETE FROM Director WHERE Id = @Id";
    sqlite3_stmt* stmt = NULL;

    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    int idArgIndex = sqlite3_bind_parameter_index(stmt, "@Id");
    ret = sqlite3_bind_int(stmt, idArgIndex, id);

    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error binding integer\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    ret = sqlite3_step(stmt);

    if (SQLITE_DONE != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error making step\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    return ret;
}

int SqlDatabaseTask (SqlDatabase* pSqlDatabase, double K, int P)
{
    const char* szSqlStatement = "SELECT * FROM Director WHERE Budget > @K AND Years < @P";
    sqlite3_stmt* stmt = NULL;

    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement(SqlDatabaseTask)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    int KArgIndex = sqlite3_bind_parameter_index(stmt, "@K");
    ret = sqlite3_bind_double(stmt, KArgIndex, K);

    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error binding double(SqlDatabaseTask)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    int PArgIndex = sqlite3_bind_parameter_index(stmt, "@P");
    ret = sqlite3_bind_int(stmt, PArgIndex, P);

    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error binding integer(SqlDatabaseTask)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    return printTable (&stmt);
}

int SqlDatabasePrintById (SqlDatabase* pSqlDatabase, int id)
{
    const char* szSqlStatement = "SELECT * FROM Director WHERE Id = @Id"; // You can't pass the table name as a parameter.
    sqlite3_stmt* stmt = NULL;

    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    int idArgIndex = sqlite3_bind_parameter_index(stmt, "@Id");
    ret = sqlite3_bind_int(stmt, idArgIndex, id);

    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error binding integer(SqlDatabasePrintById)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    return printTable (&stmt);
}

int SqlDatabaseCreateRecord (SqlDatabase* pSqlDatabase, const Record* pRec)
{
    const char* szSqlStatement = "INSERT INTO Director "
                                  "VALUES (@Id, @name, @surname, @birthday, @budget, @years)";
    sqlite3_stmt* stmt = NULL;
    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement(SqlDatabaseCreateRecord)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }


    int positions[6];
    positions[0] = sqlite3_bind_parameter_index (stmt, "@Id");
    positions[1] = sqlite3_bind_parameter_index (stmt, "@name");
    positions[2] = sqlite3_bind_parameter_index (stmt, "@surname");
    positions[3] = sqlite3_bind_parameter_index (stmt, "@birthday");
    positions[4] = sqlite3_bind_parameter_index (stmt, "@budget");
    positions[5] = sqlite3_bind_parameter_index (stmt, "@years");

    sqlite3_bind_int(stmt, positions[0], pRec->id);
    sqlite3_bind_text (stmt, positions[1], pRec->name, strlen (pRec->name), NULL);
    sqlite3_bind_text (stmt, positions[2], pRec->surname, strlen (pRec->surname), NULL);
    sqlite3_bind_text (stmt, positions[3], pRec->birthdate, strlen (pRec->birthdate), NULL);
    sqlite3_bind_double (stmt, positions[4], pRec->budget);
    sqlite3_bind_int(stmt, positions[5], pRec->years);

    ret = sqlite3_step(stmt);

    if (SQLITE_DONE != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error making step\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    sqlite3_finalize(stmt);

    return ret;
}

int  SqlDatabaseUpdate (SqlDatabase* pSqlDatabase, const Record* pRec)
{
    const char* szSqlStatement = "UPDATE Director SET Name = @name, Surname = @surname, Birthdate = @birthday,"
                                "Budget = @budget, Years = @years WHERE Id = @id;";
    sqlite3_stmt* stmt = NULL;
    int ret = sqlite3_prepare_v2(pSqlDatabase->sp->db,
                                 szSqlStatement,
                                 strlen(szSqlStatement) + 1,
                                 &stmt,
                                 NULL);
    if (SQLITE_OK != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error preparing statement(SqlDatabaseUpdateRecord)\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    int positions[6];
    positions[0] = sqlite3_bind_parameter_index (stmt, "@id");
    positions[1] = sqlite3_bind_parameter_index (stmt, "@name");
    positions[2] = sqlite3_bind_parameter_index (stmt, "@surname");
    positions[3] = sqlite3_bind_parameter_index (stmt, "@birthday");
    positions[4] = sqlite3_bind_parameter_index (stmt, "@budget");
    positions[5] = sqlite3_bind_parameter_index (stmt, "@years");

    sqlite3_bind_int(stmt, positions[0], pRec->id);
    sqlite3_bind_text (stmt, positions[1], pRec->name, strlen (pRec->name), NULL);
    sqlite3_bind_text (stmt, positions[2], pRec->surname, strlen (pRec->surname), NULL);
    sqlite3_bind_text (stmt, positions[3], pRec->birthdate, strlen (pRec->birthdate), NULL);
    sqlite3_bind_double (stmt, positions[4], pRec->budget);
    sqlite3_bind_int(stmt, positions[5], pRec->years);

    ret = sqlite3_step(stmt);

    if (SQLITE_DONE != ret)
    {
        #ifdef TEST_VERSION
        printf ("Error making step\n");
        #endif // TEST_VERSION
        sqlite3_finalize(stmt);
        return ret;
    }

    sqlite3_finalize(stmt);

    return ret;
}
