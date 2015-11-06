#include <stdio.h>
#include <stdlib.h>

int main()
{
    char resultStr[100];

    char text[] = "LOL";
    char text2[] = "BLABLA ABLAAB";
    char text3[] = "BUUK B B A A AUUK";
    char extraStr[] = "Extra str";

    char* textLines[] = {text, text2, text3};

    int linesNum = 3;

    process (resultStr, textLines, linesNum, extraStr);

    printf (resultStr);
    printf ("\n");

    return 0;
}
