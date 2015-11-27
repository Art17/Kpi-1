#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <windows.h>

const int WIDTH = 80;
const int HEIGHT = 25;

const char* comms [] =
{
    "null",
    "change",
    "rand",
    "rev",
    "neg",
    "qneg",
    "r",
    "cr",
    "step",
    "fmin",
    "swap",
    "exit"
};

const char* params [] =
{
    "",
    "%d %d",
    "%d %d",
    "",
    "",
    "",
    "%d",
    "%d",
    "%d",
    "",
    "",
    ""
};

const char* descs [] =
{
    "reset all elements",
    "change an element",
    "fill with random numbers in range",
    "reverse array",
    "show only negative numbers",
    "show quantity of negative numbers",
    "move simple right",
    "move cycle right",
    "raise to the power all elements",
    "show minimum element and index",
    "swap first minimum with last maximum",
    "exit"
};

void exit1 ()
{
    exit (1);
}

void swap (int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void swap1 (int arr[], int s)
{
    int m1 = arr[0];
    int m2 = arr[0];
    int ind1 = 0;
    int ind2 = 0;

    for (int i = 0; i < s; i++)
    {
        if (arr[i] < m1)
        {
            m1 = arr[i];
            ind1 = i;
        }
        if (arr[i] >= m2)
        {
            m2 = arr[i];
            ind2 = i;
        }
    }
    swap (&arr[ind1], &arr[ind2]);

}

void fmin1 (int arr[], int s)
{
    int m = arr[0];
    int ind = 0;

    for (int i = 0; i < s; i++)
        if (arr[i] < m)
        {
            m = arr[i];
            ind = i;
        }
    printf ("%d %d\n", m, ind);
    system ("pause");
}

void step (int arr[], int s, int p)
{
    for (int i = 0; i < s; i++)
        arr[i] = pow (arr[i], p);
}

void cr (int arr[], int s, int q)
{
    int* arr2 = malloc (s * sizeof (int));

    for (int i = 0; i < s; i++)
        arr2[(i + q) % s] = arr[i];
    for (int i = 0; i < s; i++)
        arr[i] = arr2[i];
}

void r (int arr[], int s, int q)
{
    for (int i = s - 1; i >= 0; i--)
    {
        int ind = min (s, i + q);
        arr[ind] = arr[i];
        arr[i] = 0;
    }
}

void qneg (int arr[], int s)
{
    int k = 0;
    for (int i = 0; i < s; i++)
        if (arr[i] < 0)
            k++;
    printf ("%d\n", k);
    system ("pause");
}

void neg (int arr[], int s)
{
    for (int i = 0; i < s; i++)
        if (arr[i] < 0)
            printf ("%d ", arr[i]);
    printf ("\n");
    system ("pause");
}

void rev (int arr[], int s)
{
    for (int i = 0; i < (int)s/2; i++)
        swap (&arr[i], &arr[s - i - 1]);
}

void rand1 (int arr[], int s, int a, int b)
{
    for (int i = 0; i < s; i++)
        arr[i] = rand () % (b - a + 1) + a;
}

void change (int arr[], int s, int i, int n)
{
    arr[i] = n;
}

void null (int arr[], int s)
{
    for (int i = 0; i < s; i++)
        arr[i] = 0;
}


void help ()
{
    int s = sizeof (comms) / sizeof (comms[0]);

    for (int i = 0; i < s; i++)
        printf ("   %s %s - %s\n", comms[i], params[i], descs[i]);
}

int funcs[] =
{
null,
change,
rand1,
rev,
neg,
qneg,
r,
cr,
step,
fmin1,
swap1,
exit1
};

int main()
{
    srand (time (NULL));

    const int nMax = 10;
    int n;
    int* arr;
    printf ("Write n: ");
    scanf ("%d", &n);

    if (n <= nMax)
        arr = malloc(n*sizeof(int));
    if (arr == NULL || n > nMax)
    {
        printf ("Error");
        return 0;
    }

    system ("cls");

    for (int i = 0; i < n; i++)
        arr[i] = 0;

    for (int i = 0; i < n; i++)
        printf ("%d ", arr[i]);
    printf ("\n");

    for (int i = 0; i < WIDTH; i++)
        printf ("-");

    const int strMax = 10;
    char str[strMax];

    while (1)
    {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD pos;
            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);

            system ("cls");
        for (int i = 0; i < n; i++)
            printf ("%d ", arr[i]);
        printf ("\n");
        for (int i = 0; i < WIDTH; i++)
            printf ("-");
        printf ("Write command: ");
        fflush(stdin);
        gets (str);

        if ( strcmp (str, "help") == 0 )
        {
            help ();
        }

        int c = -1;
        int q = sizeof (comms) / sizeof (comms[0]);

        for (int i = 0; i < q; i++)
            if ( strncmp ( comms[i], str, strlen(comms[i]) ) == 0 )
            {
                c = i;
                break;
            }

        if (c == -1)
            continue;

        int p1 = INT_MIN, p2 = INT_MIN, p3 = INT_MIN;

        sscanf (str + strlen (comms[c]) + 1, params[c], &p1, &p2);

        void (*f)(int [], int, int, int) = funcs[c];
        f (arr, n, p1, p2);

    }

    return 0;
}
