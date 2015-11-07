#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

const int n0 = 4;
const int n1 = 1;

const int nMax = 511;
int counts[nMax];

int max (int x, int y)
{
    return (x > y) ? x : y;
}
int min (int x, int y)
{
    return x < y ? x : y;
}

void fillRand2 (int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = (rand () % 511) - 255;
}

int checkRand2 (int arr[], int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i] > 255 && arr[i] < -255)
            return 0;
    return 1;
}

int maxValue (int arr[], int size)
{
    int m = arr[0];

    for (int i = 0; i < size; i++)
        m = max (m, arr[i]);

    return m;
}

int minIndex (int arr[], int size)
{
    int m = arr[0], index = -1;

    for (int i = 0; i < size; i++)
        m = min (m, arr[i]);
    for (int i = 0; i < size; i++)
        if (arr[i] == m)
        {
            index = i;
            break;
        }
    return index;
}

int maxOccurance (int arr[], int size)
{
    int m = 0;

    for (int i = 0; i < size; i++)
        m = max (m, ++counts[arr[i] + 255]);

    for (int i = nMax - 1; i >= 0; i--)
        if ( counts[i] == m )
            return i - 255;
}

int diff (int arr1[], int arr2[], int res[], int size)
{
    int bZero = 1;

    for (int i = 0; i < size; i++)
    {
        res[i] = arr1[i] - arr2[i];
        if (res[i] != 0)
            bZero = 0;
    }
}

void add (int arr1[], int arr2[], int res[], int size)
{
    for (int i = 0; i < size; i++)
        res[i] = arr1[i] + arr2[i];
}

int gteq (int arr1[], int arr2[], int size)
{
    for (int i = 0; i < size; i++)
        if (arr1[i] < arr2[i])
            return 0;
    return 1;
}

void lor (int arr1[], int arr2[], int res[], int size)
{
    for (int i = 0; i < size; i++)
        res[i] = arr1[i] || arr2[i];
}

void printArr (int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf ("%d ", arr[i]);
    printf ("\n\n");
}

int main ()
{
    srand (time (NULL));

    const int size = 20;
    int arr1[size];
    int arr2[size];
    int res[size];

    fillRand2 (arr1, size);
    fillRand2 (arr2, size);

    printf ("First array: \n");
    printArr (arr1, size);

    printf ("check interval: %d\n\n", checkRand2 (arr1, size));

    printf ("Max element: %d\n\n", maxValue (arr1, size));

    printf ("Min index: %d\n\n", minIndex (arr1, size));

    printf ("Max occurance: %d\n\n", maxOccurance (arr1, size));

    printf ("First array: \n");
    printArr (arr1, size);

    printf ("Second array: \n");
    printArr (arr2, size);

    printf ("diff result: %d\n\n", diff (arr1, arr2, res, size));
    printf ("res array: \n");
    printArr (res, size);

    add (arr1, arr2, res, size);
    printf ("Add res: \n");
    printArr (res, size);

    printf ("Greater than or equals: %d\n\n", gteq (arr1, arr2, size));

    for (int i = 0; i < size; i++)
    {
        arr1[i] = (arr1[i] + 255) % 2;
        arr2[i] = (arr2[i] + 255) % 2;
    }

    printf ("First array: \n");
    printArr (arr1, size);

    printf ("Second array: \n");
    printArr (arr2, size);

    lor (arr1, arr2, res, size);
    printf ("Lor res: \n");
    printArr (res, size);

    return 0;
}
