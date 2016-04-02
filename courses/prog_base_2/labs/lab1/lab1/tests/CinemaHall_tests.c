#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "tests.h"
#include "../cinemahall.h"

static void new__int__relevantSize (void** state)
{
    CinemaHall cinema;
    CinemaHall_initialize(&cinema, 20);

    assert_int_equal (CinemaHall_getQuantity(&cinema), 20);

    CinemaHall_deinitialize(&cinema);
}

static void new__int__invalidSize (void** state)
{
    CinemaHall cinema;
    CinemaHall_initialize(&cinema, -1);

    assert_int_equal (CinemaHall_getQuantity(&cinema), 10);

    CinemaHall_deinitialize(&cinema);
}

static void getQuantity__void__relevantSize (void** state)
{
    CinemaHall cinema;
    CinemaHall_initialize(&cinema, 5);

    assert_int_equal (CinemaHall_getQuantity(&cinema), 5);

    CinemaHall_deinitialize(&cinema);
}

static void getSeatState__CinemaHall__pos__SeatState (void** state)
{
    CinemaHall cinema;
    CinemaHall_initialize(&cinema, 5);

    CinemaHall_setSeatState(&cinema, 3, SEAT_BOOKED);

    assert_int_equal (CinemaHall_getSeatState(&cinema, 3), SEAT_BOOKED);

    CinemaHall_deinitialize(&cinema);
}

static void setSeatState__CinemaHall__pos__state__PrevSeatState (void** state)
{
    CinemaHall cinema;
    CinemaHall_initialize(&cinema, 5);

    CinemaHall_setSeatState(&cinema, 3, SEAT_BOUGHT);

    assert_int_equal (CinemaHall_setSeatState(&cinema, 3, SEAT_BOOKED), SEAT_BOUGHT);

    CinemaHall_deinitialize(&cinema);
}

void moduleTests_CinemaHall(void) {
    const UnitTest tests[] =
    {
        unit_test(new__int__relevantSize),
        unit_test(new__int__invalidSize),
        unit_test(getQuantity__void__relevantSize),
        unit_test(getSeatState__CinemaHall__pos__SeatState),
        unit_test(setSeatState__CinemaHall__pos__state__PrevSeatState)
    };
    return run_tests(tests);
}
