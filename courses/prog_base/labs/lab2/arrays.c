#include <math.h>
#include <stdlib.h>

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
