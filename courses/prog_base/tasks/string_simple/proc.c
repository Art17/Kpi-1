/* New */
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

char* process (char* resultStr, const char* textLines[], int linesNum, const char* extraStr)
{
    int resInd = 0;
    char curNums[100];
    char resNums[100];
    int i;
    strcpy (curNums, "\0");
    strcpy (resNums, "NULL");
    for (i = 0; i < linesNum; i++)
    {
        if (calcNum (textLines[i], curNums) == 0)
        {
            resInd = i+1;
            strcpy (resNums, curNums);
        }
    }
    if (resInd == 0)
        sprintf (resultStr, "%d %s %s", resInd, resNums, extraStr);
    else
        sprintf (resultStr, "%d %s", resInd, resNums);

    return resultStr;
}
