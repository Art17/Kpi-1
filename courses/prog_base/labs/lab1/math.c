double calc (double x, double y, double z)
{
    int n0 = 4;
    int n1 = 1;

    if (x - y == 0 || x == 0 || sin(x) == 0 || z == 0)
        return NAN;

    double a0 = pow (x, y+1) / pow (x - y, 1/z);
    double a1 = n0*y + z/x;
    double a2 = sqrt (fabs( cos(y)/sin(x) + n1 ));

    double a = a0 + a1 + a2;

    if ( isnan(a) )
        return NAN;

    return a;
}