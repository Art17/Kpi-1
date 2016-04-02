#include "tests.h"

void totalTests(void)
{
    puts("CinemaHall tests:");
    moduleTests_CinemaHall();
    puts("\n\nClient tests:");
    moduleTests_Client();
}
