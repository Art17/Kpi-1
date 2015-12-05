#include <stdio.h>
#include <stdlib.h>

int  fmin (char str[], int i)
{
    if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 70) || (str[i] >= 97 && str[i] <= 102))
        return str[i];
    if (str[i] == '\0')
        return -1;
    return fmin (str, ++i);
}

int  fmax (char str[], int i)
{
    if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 70) || (str[i] >= 97 && str[i] <= 102))
        return str[i];
    if (i == 0)
        return -1;
    return fmax (str, --i);
}

int min (int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    const int nMax = 256;
    char str[nMax];

    scanf ("%s", str);
    int n = strlen (str);

    printf ("%c\n", min ( fmin(str, 0), fmax(str, n-1) ));

    return 0;
}
