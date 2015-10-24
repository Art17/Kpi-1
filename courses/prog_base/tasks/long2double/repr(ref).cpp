#include <cstdio>

double long2double_ref (long long ll)
{
    return (double&)ll;
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

    printf ("ref: \n");
    printf ("%.325lf\n\n", long2double_ref (ll));

	scanf ("%d",&ll);
	return 0;
}
