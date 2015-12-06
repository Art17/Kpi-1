#include <stdio.h>
#include <stdlib.h>

// [0;9] - [48;57]
// [A;Z] - [65;90]
// .     - 46

const int lMax = 64;

char* ns_convert (char* number, unsigned int sourceBase, unsigned int destBase)
{
    const int precision = 12;
    const double eps = 10e-6;

    if (sourceBase <= 1 || sourceBase >= 37 || destBase <= 1 || destBase >= 37)
        return "\0";

    int p = 0;
    char ch = *number;
    int maxFigure = -1;
    int left = 0, right = 0, isDouble = 0;
    int sourceFigures[lMax + 16];
    int destFigures[lMax + 16];
    int length = 0;

    while (ch != '\0')
    {
        int f = 0;
        if (ch >= 48 && ch <= 57)
            f = ch - 48;
        else if (ch >= 65 && ch <= 90)
            f = ch - 55;
        else if (ch == 46)
            f = -1, isDouble++;
        else
            return "\0";
        maxFigure = (maxFigure > f) ? maxFigure : f;

        if (f != -1)
            sourceFigures[length++] = f;

        if (ch != '.')
            isDouble ? right++ : left++;
        p++;
        ch = *(number + p);
    }

    if (isDouble >= 2)
        return "\0";
    if (maxFigure > sourceBase-1)
        return "\0";

    double number10 = 0;
    double m = 1;

    for (int i = left-1; i >= 0; i--, m *= sourceBase)
        number10 += sourceFigures[i]*m;
    m = 1./sourceBase;
    for (int i = left; i < length; i++, m/=sourceBase)
        number10 += sourceFigures[i]*m;

    long long intPart = (long long)number10;
    double doublePart = number10 - intPart;

    p = 0;
    while (intPart >= destBase)
    {
        destFigures[p++] = intPart%destBase;
        intPart /= destBase;
    }
    destFigures[p++] = intPart;

    left = p;
    right = precision;

    for (int i = 0; i < precision; i++)
    {
        doublePart *= destBase;
        int t = (int)doublePart;
        destFigures[p++] = t;
        if (doublePart < eps)
        {
            right = i;
            break;
        }
        doublePart -= t;
    }

    length = left + right;
    int size = (length) + (right > 0 ? 1 : 0) + 1;
    char* destNumber = malloc(size);
    p = 0;

    for (int i = left - 1; i >= 0; i--)
        destNumber[p++] = (destFigures[i] <= 9) ? (destFigures[i] + 48) : (destFigures[i] + 55);

    if (right > 0)
        destNumber[p++] = '.';

    for (int i = left; i < length; i++)
        destNumber[p++] = (destFigures[i] <= 9) ? (destFigures[i] + 48) : (destFigures[i] + 55);

    destNumber[p++] = '\0';

    return destNumber;
}
