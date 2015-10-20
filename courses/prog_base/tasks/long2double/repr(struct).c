#include <stdio.h>

double long2double_struct (long long ll)
{
    struct LongDouble
    {
        long long L[1];
        double D[1];
    } ld;
    ld.L[1] = ll; // out of bound
    return ld.D[0];
}

double long2double_pointer (long long ll)
{
    return *((double*)&ll);
}

int main ()
{
    long long ll = -12432656943232423ll;

    printf ("pointer: \n");
    printf ("%.325lf\n\n", long2double_pointer (ll));

    printf ("struct: \n");
    printf ("%.325lf\n\n", long2double_struct (ll));

    return 0;
}
