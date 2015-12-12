#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void zeroArr (int counts[], int size)
{
    for (int i = 0; i < size; i++)
        counts[i] = 0;
}

int main(int argc, char* argv[])
{
    char input[256];
    char output[256];

    if (argc < 2)
    {
        printf ("Error no console params");
        return 0;
    }

    strcpy (input, argv[1]);
    strcpy (output, argv[2]);

    /*printf ("input file: ");
    scanf ("%s", input);

    printf ("output file: ");
    scanf ("%s", output);*/

    FILE* pIn = fopen (input, "r");
    FILE* pOut = fopen (output, "w");

    char line[256];
    char line2[256];
    char vowels [] = {'A', 'E', 'I', 'O', 'U', 'Y'};
    int size = sizeof (vowels) / sizeof (char);
    int counts [ size ];

    zeroArr (counts, size);

    while ( fgets (line, 256, pIn) != NULL )
    {
        for (int i = 0; i < strlen (line); i++)
        {
            line2[i] = toupper (line[i]);

            for (int j = 0; j < size; j++)
                if (line[i] == vowels[j] || line[i] == tolower(vowels[j]))
                    counts[j]++;
        }
        line2[strlen(line)] = '\0';
        fputs (line2, pOut);
        for (int i = 0; i < size; i++)
            if (counts[i] > 0)
                fprintf (pOut, "%c %d\n", vowels[i], counts[i]);
        zeroArr (counts, size);
    }

    fclose (pOut);
    fclose (pIn);

    return 0;
}
