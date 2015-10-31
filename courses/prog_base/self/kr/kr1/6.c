#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max (int a, int b)
{
    return a > b ? a : b;
}

void find (int* arr, int N)
{
    printf ("array: ");
    for (int i = 0; i < N; i++)
        printf ("%d ", arr[i]);
    printf ("\n");

    for (int i = 0; i < N; i++)
        if (arr[i] == -1)
            printf ("%d ", i);
    printf ("\n");
}

int main()
{
    srand (time (NULL));

    int N, M;
    scanf ("%d %d", &N, &M);

    if (N <= 0 && N >= 1000000 && M < 0 && M > 1000000)
    {
        printf ("error\n");
        return 0;
    }
    int arr[N];

    for (int i = 0; i < N; i++)
        arr[i] = -1;

    int help[N];
    for (int i = 0; i < N; i++)
        help[i] = i;
    for (int i = 0; i < N; i++)
    {
        int temp = help[i];
        int a = rand () % N;
        help[i] = help[a];
        help[a] = temp;
    }

    for (int i = 0; i < max(0, N-M); i++)
        arr[help[i]] = rand () % (N + M);
    find (arr, N);

    return 0;
}
