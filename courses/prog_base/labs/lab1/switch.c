int min (int a, int b)
{
    return a < b ? a : b;
}

int max (int a, int b)
{
    return a > b ? a : b;
}

int exec(int op, int a, int b)
{
    int n0 = 4;
    int n1 = 1;

   if (op < 0)
    op*=-1, a=a+b, b=a-b, a-=b;

   switch (op)
   {
   case 0:
       return -a;
   case 1:
       return a+b;
   case 2:
       return a-b;
   case 3:
       return a*b;
   case 4:
       return b == 0 ? NAN : a/b;
   case 5:
       return abs(a);
   case 6:
       return pow(a, b);

   case 7:
   case 13:
   case 77:
       return b == 0 ? NAN : a%b;
   case 8:
       return max(a, b);
   case 9:
       return min (a, b);
   case 10:

       switch (abs(b) % 8)
       {
       case 0:
           return abs(a) * sizeof(char);
       case 1:
           return abs(a) * sizeof (signed char);
       case 2:
           return abs(a) * sizeof (short);
       case 3:
           return abs(a) * sizeof (unsigned int);
       case 4:
           return abs(a) * sizeof (long);
       case 5:
           return abs(a) * sizeof (unsigned long long);
       case 6:
           return abs(a) * sizeof (float);
       case 7:
           return abs(a) * sizeof (double);
       }

   case 11:
    if (a - n1 == 0)
        return NAN;
       else
        return (n0 + 1)*cos(b*M_PI) / (a - n1);
   default:
       if (op < 100)
       {
           if ( abs(a+1) == 0 || abs(b+1) == 0 )
            return NAN;
           else
            return ( op % abs(a+1) ) + (op + abs(b+1));
       }
       else
        return -1;
   }
}