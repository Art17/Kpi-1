#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "cmocka.h"

#include "tests.h"
#include "../communicator.h"
#include "../comnet.h"


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

static void getName__void__DefaultName (void** state)
{
    communicator_t communicator = communicator_new ();
    const char* tempName = "temp";

    char buffer [256];
    communicator_getName (communicator, buffer);

    assert_string_equal (tempName, buffer);

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

static void setName__NullString__tempName (void** state)
{
    communicator_t communicator = communicator_new ();
    const char* name = NULL;
    communicator_setName (communicator, name);

    char buffer [256];
    communicator_getName (communicator, buffer);

    assert_string_equal ("temp", buffer);

    communicator_free (communicator);
}

static void setOnMessageReceived__MessageReceivedFunc__callbackCalled (void** state)
{
    communicator_t rec = communicator_new ();
    communicator_t send = communicator_new ();
    comnet_t comnet = comnet_new ();
    int callbackCalled = 0;
    const char* message = "Hello";

    int onMessageReceived (communicator_t r, communicator_t s, const char* m)
    {
        assert_true (r == rec);
        assert_true (s == send);
        assert_string_equal (m, message);
        callbackCalled = 1;
        return 0;
    }

    communicator_setOnMessageReceived(rec, onMessageReceived);

    comnet_sendMessage(comnet, rec, send, message);

    assert_int_equal(callbackCalled, 1);

    comnet_free (comnet);
    communicator_free (send);
    communicator_free (rec);
}

static void setOnSuspiciousFunc__SuspiciousFunc__callbackCalled (void** state)
{
    communicator_t rec = communicator_new ();
    communicator_t send = communicator_new ();
    comnet_t comnet = comnet_new ();
    int callbackCalled = 0;
    const char* message = "Hello";

    int onSuspiciousActivity (communicator_t s)
    {
        assert_true (s == send);
        callbackCalled = 1;
        return 0;
    }

    communicator_setOnSuspiciousActivity(send, onSuspiciousActivity);

    for (int i = 0; i < 11; i++)
        comnet_sendMessage(comnet, rec, send, message);

    assert_int_equal(callbackCalled, 1);

    comnet_free (comnet);
    communicator_free (send);
    communicator_free (rec);
}

void moduleTests_Communicator(void) {
    const UnitTest tests[] =
    {
        unit_test(getName__string__relevantName),
        unit_test(getName__void__DefaultName),
        unit_test(setName__string__relevantName),
        unit_test(setName__NullString__tempName),
        unit_test(setOnMessageReceived__MessageReceivedFunc__callbackCalled),
        unit_test(setOnSuspiciousFunc__SuspiciousFunc__callbackCalled)
    };
    return run_tests(tests);
}
