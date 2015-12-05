#include <stdio.h>
#include <stdlib.h>

void fprocess (const char* pread, const char* pwrite)
{
    FILE* pIn = fopen (pread, "r");
    FILE* pOut = fopen (pwrite, "w");

    const int n = 1024;
    const int var = 14;
    char str[n];

    for (int i = 0; i < var-1; i++)
        fgets (str, sizeof (str), pIn);
    int a, b;

    fscanf (pIn, "%d=%d", &a, &b);

    if (a == b)
        fprintf (pOut, "true\n");
    else
        fprintf (pOut, "false\n");

    fclose (pOut);
    fclose (pIn);
}