#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "tests.h"
#include "../client.h"

static void initialize__int__InvalidMaxSeat (void** state)
{
    Client client;
    Client_initialize(&client, -1);

    assert_int_equal(Client_getMaxSeat(&client), 10);

    Client_deinitialize(&client);
}

static void initialize__int__relevantMaxSeat (void** state)
{
    Client client;
    Client_initialize(&client, 5);

    assert_int_equal(Client_getMaxSeat(&client), 5);

    Client_deinitialize(&client);
}

static void getId__void__relevantId (void** state)
{
    Client client;
    Client_initialize(&client, 5);

    assert_int_equal(Client_getId(&client), 2);

    Client_deinitialize(&client);
}

void moduleTests_Client(void) {
    const UnitTest tests[] =
    {
        unit_test (initialize__int__InvalidMaxSeat),
        unit_test (initialize__int__relevantMaxSeat),
        unit_test (getId__void__relevantId)
    };
    return run_tests(tests);
}
