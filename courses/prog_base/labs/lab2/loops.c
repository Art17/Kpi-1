double calc (int n, int m)
{
    double x = 0.;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            x += cos (i*M_PI/2) + (n1 + 1)*sin(j*M_PI/4);
    return x;
}
