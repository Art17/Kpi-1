#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
    int h = 1, m = 22, code = 6112;
    double res = 0;
    switch (code)
    {
    case 44:
        res = (h*60 + m)*0.77;
        break;
    case 62:
        res = (h*60 + m)*0.8;
        break;
    case 32:
        res = (h*60 + m)*0.95;
        break;
    case 697:
    case 692:
        res = (h*60 + m)*1.5;
        break;
    default:
        if (code >= 10 && code <= 999)
            res = (h*60 + m);
        else
        {
            printf ("Error");
            return 0;
        }
        break;
    }
    printf ("%f", res);
    return 0;
}
