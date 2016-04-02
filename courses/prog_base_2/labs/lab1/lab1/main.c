#include <stdio.h>
#include <stdlib.h>

#include "errormodule.h"
#include "cinemahall.h"
#include "console.h"
#include "client.h"

void emulate_cinema ()
{
    srand (time (NULL));

    CinemaHall cinema;
    const int maxSeat = 2080;
    CinemaHall_initialize(&cinema, maxSeat);
    FILE* pLog = fopen ("log.txt", "w");

    Console console;
    Console_initialize (&console, 150, 47);

    Console_showCinema(&console);

    const int qClients = 600;
    const int updateSpeed = 1;
    Client clients[qClients];

    for (int i = 0; i < qClients; i++)
        Client_initialize (&clients[i], maxSeat);

    for (int i = 0; i < qClients; i++)
    {
        int seatNumber = -1, seatState = -1;
        Client_getAction(&clients[i], &seatNumber, &seatState);
        if ( CinemaHall_getSeatState(&cinema, seatNumber) == SEAT_AVAILABLE )
        {
            if (seatState == SEAT_BOUGHT)
            {
                fprintf (pLog, "Client %d has bought seat number: %d\n", i, seatNumber);
            }
            if (seatState == SEAT_BOOKED)
            {
                fprintf (pLog, "Client %d has booked seat number: %d\n", i, seatNumber);
            }
            CinemaHall_setSeatState(&cinema, seatNumber, seatState);
        }
        else
        {
            fprintf (pLog, "Client %d access to seat number %d denied\n", i, seatNumber);
        }
        //Sleep (100);
        if (i % (qClients/20*updateSpeed) == 0)
        Console_showCinemaHall(&console, &cinema);
    }

    for (int i = 0; i < qClients; i++)
        Client_deinitialize(&clients[i]);

    fclose (pLog);

    Console_deinitialize(&console);
    CinemaHall_deinitialize(&cinema);

    Sleep (INFINITE);
}

void test_all ()
{
    totalTests ();
}

int main()
{
    //emulate_cinema();
    test_all ();

    return 0;
}
