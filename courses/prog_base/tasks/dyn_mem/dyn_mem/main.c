#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* str = (char*)malloc (256*sizeof (char));

    if (!str)
    {
        printf ("Error\n");
        return 0;
    }

    scanf ("%s", str);

    char *curPtr = str;
    char *minv = NULL, *maxv = NULL;

    while (*curPtr != '\0')
    {
        if ((*curPtr >= 48 && *curPtr <= 57) && (minv == NULL))
            minv = curPtr;
        if ((*curPtr >= 48 && *curPtr <= 57) && (minv != NULL))
            maxv = curPtr;
        curPtr++;
    }
    if (minv == NULL)
    {
        printf ("No figures\n");
        return 0;
    }
    printf ("%d\n", (*minv - 48)+(*maxv - 48));

    free (str);

    return 0;
}
