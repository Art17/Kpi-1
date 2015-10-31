#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {5, 4};
    int size = sizeof (arr) / sizeof (int);

    printf ("source array: ");
    for (int i = 0; i < size; i++)
        printf ("%d ", arr[i]);
    printf ("\n");

    printf ("result: ");
    if (size == 0 || size == 1)
    {
        printf ("error\n");
        return 0;
    }
    for (int i = 0; i < size - 1; i++)
        printf ("%d ", arr[i] - arr[i+1]);
    printf ("\n");

    return 0;
}
