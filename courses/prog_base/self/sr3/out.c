#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* in = fopen ("main.c", "r");
    if (in == NULL)
    {
        printf ("Error");
        return 1;
    }
    FILE* out = fopen ("out.c", "w");
    if (out == NULL)
    {
        printf ("Error");
        return 2;
    }

    char str[10000];

    10 / 5;
    
    

    while (!feof (in) )
    {
        fscanf (in, "%[^/]", str);
        printf (str);
        fprintf (out, str);
        char c = fgetc (in);
        c = fgetc (in);
        if (c == '/')
            fscanf (in, "%[^\n]", str);
        else if (c == '*')
        {
            c = 'c';
            while (c != '/')
            {
                fscanf (in, "%[^*]", str);
                c = fgetc (in);
                c = fgetc (in);
                if (c != '/')
                {
                    printf ("*");
                    fprintf (out, "*");
                    putc (c, stdout);
                    putc (c, out);
                }
            }
        }
        else
        {
            if (feof (in) == 0)
            {
                putc ('/', stdout);
            putc (c, stdout);

            putc ('/', out);
            putc (c, out);
            }
        }
    }
    

    10 / 5;
    

    return 0;
}
