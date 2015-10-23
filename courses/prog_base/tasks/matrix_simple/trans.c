#include <stdio.h>
#include <stdlib.h>

const int matX = 4;
const int matY = 4;
// n0 = 4
// n1 = 1

void fillRand (int mat[4][4])
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

void rotateCCW180 (int mat[4][4])
{
    for (int i = 0; i < matX/2; i++)
        for (int j = 0; j < matY; j++)
            swap (&mat[i][j], &mat[matX-i-1][matY-j-1]);
}

void flipV (int mat[4][4])
{
    for (int i = 0; i < matX/2; i++)
        for (int j = 0; j < matY; j++)
            swap (&mat[i][j], &mat[matX-i-1][j]);
}

void transposMain (int mat[4][4])
{
    for (int i = 0; i < matX - 1; i++)
        for (int j = i + 1; j < matY; j++)
            swap (&mat[i][j], &mat[j][i]);
}