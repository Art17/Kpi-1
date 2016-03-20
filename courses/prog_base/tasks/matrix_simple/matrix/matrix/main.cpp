#include <stdio.h>
#include <stdlib.h>

const int matX = 4;
const int matY = 4;
// n0 = 4
// n1 = 1

void fillRand (int mat[matX][matY])
{
    for (int i = 0; i < matX; i++)
        for (int j = 0; j < matY; j++)
            mat[i][j] = (rand () % 1999) - 999;
}

void swap (int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void rotateCCW180 (int mat[matX][matY])
{
    for (int i = 0; i < matX/2; i++)
        for (int j = 0; j < matY; j++)
            swap (&mat[i][j], &mat[matX-i-1][matY-j-1]);
}

void flipV (int mat[matX][matY])
{
    for (int i = 0; i < matX/2; i++)
        for (int j = 0; j < matY; j++)
            swap (&mat[i][j], &mat[matX-i-1][j]);
}

void transposMain (int mat[matX][matY])
{
    for (int i = 0; i < matX - 1; i++)
        for (int j = i + 1; j < matY; j++)
            swap (&mat[i][j], &mat[j][i]);
}

void printMat (int mat[matX][matY])
{
    for (int i = 0; i < matX; i++)
    {
        for (int j = 0; j < matY; j++)
            if (j < matY - 1)
                printf ("%4d     ", mat[i][j]);
            else
                printf ("%4d", mat[i][j]);
        printf ("\n");
    }
    printf ("\n");
}

int main ()
{
    int mat[matX][matY];

    fillRand (mat);
    printf ("Original: \n");
    printMat (mat);

    rotateCCW180 (mat);
    printf ("Rotated 180: \n");
    printMat (mat);

    flipV (mat);
    printf ("Fliped: \n");
    printMat (mat);

    transposMain (mat);
    printf ("TransposMain: \n");
    printMat (mat);


    return 0;
}
