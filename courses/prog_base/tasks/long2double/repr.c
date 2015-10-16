#include <math.h>

double long2double (long long ll)
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
