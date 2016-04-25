#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "communicator.h"
#include "comnet.h"

#define COMMUNICATOR_SIZE 5

int onSuspiciousActivity (communicator_t c)
{
    printf ("com %d is suspicious(more than 10 messages)\n", communicator_getId (c));

    return 0;
}

int onMessageReceived (communicator_t c, const char* message)
{
    printf ("com %d received message\n", communicator_getId (c));
    printf ("\tmessage: %s\n", message);

    return 0;
}

void emulateCommunicators (void);

int main()
{
    emulateCommunicators ();
    printf ("\n\n----------------Unit tests-----------------\n\n");
    totalTests ();

    return 0;
}

void emulateCommunicators (void)
{
    srand (time (NULL));

    communicator_t communicators[COMMUNICATOR_SIZE];
    comnet_t comnet;

    for (int i = 0; i < COMMUNICATOR_SIZE; i++)
        communicators[i] = communicator_new ();
    comnet = comnet_new ();

    for (int i = 0; i < COMMUNICATOR_SIZE; i++)
    {
        communicator_setOnMessageReceived(communicators[i], onMessageReceived);
        communicator_setOnSuspiciousActivity (communicators[i], onSuspiciousActivity);
        comnet_subscribeMessageSending(comnet, communicators[i], communicator_getCommunicatorMessageSending (communicators[i]));
    }
    for (int i = 0; i < 10; i++)
    {
        printf ("\n\n--------------------------------\n\n");
        int receiverInd = rand () % COMMUNICATOR_SIZE;
        char buffer[256];
        sprintf (buffer, "Hello communicator %d", receiverInd);
        comnet_sendMessage (comnet, communicators[receiverInd], communicators[4], buffer);
    }

    for (int i = 0; i < COMMUNICATOR_SIZE; i++)
        communicator_free ( communicators[i] );
    comnet_free (comnet);
}
