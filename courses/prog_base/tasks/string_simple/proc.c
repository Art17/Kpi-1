#include <string.h>

int isVowel (char ch)
{
    if (strchr("aeiouAEIOU", ch) != NULL)
        return 1;
    else
        return 0;
}

int calcNum (char* str, char* resStr)
{
    int res;
    char* p;
    strcpy (resStr, "\0");
    res = 0;
    p = strtok (str, " ");
    while (p != NULL)
    {
        int a = strlen (p);
        if (isVowel (p[0]))
            a*=-1;
        res += a;
        sprintf (resStr, "%s%d, ", resStr, a);
        p = strtok (NULL, " ");
    }
    return res;
}

char process (char* resultStr, const char* textLines[], int linesNum, const char* extraStr)
{
    int ind = -1;
    char temp[100];
    char resStr[100];
    int i;
    strcpy (resStr, "\0");
    for (i = 0; i < linesNum; i++)
    {
        if (calcNum (textLines[i], temp) == 0)
        {
            ind = i;
            strcpy (resStr, temp);
        }
    }
    sprintf (resultStr, "%d %s", ind, resStr);
}
