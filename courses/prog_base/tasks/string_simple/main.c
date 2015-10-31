#include <stdio.h>
#include <stdlib.h>

int main()
{
    char resultStr[100];

    char text[] = "My name is Artem";
    char text2[] = "BLABLA ABLAAB";
    char text3[] = "BUUK B B A A AUUK";

    char* textLines[] = {text, text2, text3};

    int linesNum = 3;
    char extraStr[100];

    process (resultStr, textLines, linesNum, extraStr);

    printf (resultStr);
    printf ("\n");

    return 0;
}
