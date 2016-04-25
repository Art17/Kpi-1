#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "cmocka.h"

#include "tests.h"
#include "../communicator.h"


static void getName__string__relevantName (void** state)
{
    communicator_t communicator = communicator_new ();
    const char* name = "name";
    communicator_setName (communicator, name);

    char buffer [256];
    communicator_getName (communicator, buffer);

    assert_string_equal (name, buffer);

    communicator_free (communicator);
}

static void setName__string__relevantName (void** state)
{
    communicator_t communicator = communicator_new ();
    const char* name = "name";
    communicator_setName (communicator, name);

    char buffer [256];
    communicator_getName (communicator, buffer);

    assert_string_equal (name, buffer);

    communicator_free (communicator);
}

void moduleTests_Communicator(void) {
    const UnitTest tests[] =
    {
        unit_test(getName__string__relevantName),
        unit_test(setName__string__relevantName),
    };
    return run_tests(tests);
}
