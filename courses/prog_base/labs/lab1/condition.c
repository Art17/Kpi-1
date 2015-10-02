int check (int max, int min)
{
    int r = 1;
    while (min--)
    {
        r *= max;
        if (r > 32767)
            return 0;
    }
    return 1;
}

int min (int a, int b)
{
    return a < b ? a : b;
}

int max (int a, int b)
{
    return a > b ? a : b;
}

int satisfies(int a, int b, int c)
{
   int n0 = 4;
   int n1 = 1;
   int mn = min (a, min(b,c));
   int mx = max (a, max(b,c));
   int md = a + b + c - mn - mx;

   if (mx < 0)
   {
       int modmin = abs(mn);
       int sum2 = a + b + c - mn;
       if (sum2 < -256 && modmin < 256 && (modmin & (modmin-1)) == 0)
        return 1;
       else
        if ( abs(sum2-modmin) < 16 || abs(sum2) < 16 )
            return 1;
        else
            return 0;
   }
   if (a < 0 || b < 0 || c < 0)
   {
       if (mn < 0 && md >= 0)
        return mn > -256;
       else
        return (mn + md)*(n0+n1) > -256;

   }
   if (mn >= 0)
       return check (mx, mn);
}