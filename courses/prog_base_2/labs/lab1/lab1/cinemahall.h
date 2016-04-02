#ifndef CINEMAHALL_H_INCLUDED
#define CINEMAHALL_H_INCLUDED

typedef struct tagCinemaHall_Private CinemaHall_Private;

#define SEAT_AVAILABLE 0
#define SEAT_BOUGHT 1
#define SEAT_BOOKED 2
#define SEAT_DENIED 3

typedef struct
{
    CinemaHall_Private* chp;
} CinemaHall;

int CinemaHall_initialize (CinemaHall* , int);
int CinemaHall_deinitialize (CinemaHall* );

int CinemaHall_getQuantity (CinemaHall*);

int CinemaHall_getSeatState (CinemaHall*, int);
int CinemaHall_setSeatState (CinemaHall*, int, int);

char* CinemaHall_errorCode_toString (int);

#endif // CINEMAHALL_H_INCLUDED
