#include <stdio.h>

double long2double_union (long long ll)
{
    union LongDouble
    {
        long long ll;
        double d;
    } ld;
    ld.ll = ll;
    return ld.d;
}

#include <memory.h>
double long2double_memcpy (long long ll)
{
    long long A[1];
    double B[1];

    A[0] = ll;
    memcpy (B, A, sizeof (long long));
    return B[0];
}

double long2double_pointer (long long ll)
{
    return *((double*)&ll);
}
#include <math.h>
double long2double_algorithm (long long ll)
{
    int bits[64];

    for (int i = 63; i >= 0; ll >>= 1, i--)
        bits[i] = ll & 1;

    int s = bits[0];

    int e = 0;
    for (int i = 1; i <= 11; i++)
        e += bits[i] ? (int)pow (2, 11 - i) : 0;

    double m = 0;
    for (int i = 12; i <= 63; i++)
        m += bits[i] ? pow (2, 11 - i) : 0;

    if (e == 2047 && m != 0)
        return NAN;
    if (s == 1 && e == 2047 && m == 0)
        return -INFINITY;
    if (s == 0 && e == 2047 && m == 0)
        return INFINITY;
    if (e > 0 && e < 2047)
        return pow (-1, s) * pow (2, e - 1023) * (m + 1);
    if (e == 0 && m != 0)
        return pow (-1, s) * pow (2, -1022) * m;
    if (e == 0 && m == 0 && s == 1)
        return -0.;
    if (e == 0 && m == 0 && s == 0)
        return 0.;
}

long long double2long (double d)
{
    return *((long long*)&d);
}


int main ()
{
    long long ll = -12432656943232423ll;

    printf ("union: \n");
    printf ("%.325lf\n\n", long2double_union (ll));

    printf ("pointer: \n");
    printf ("%.325lf\n\n", long2double_pointer (ll));

    printf ("memcpy: \n");
    printf ("%.325lf\n\n", long2double_memcpy (ll));

    printf ("algorithm: \n");
    printf ("%.325lf\n\n", long2double_algorithm (ll));

    return 0;
}
