#include "communicator.h"

static int lastId = 0;

struct communicator_s
{
    char name [24];
    int qMessages;
    SuspiciousFunc onSuspiciousActivity;
    MessageReceivedFunc onMessageReceived;
    int id;
};

communicator_t communicator_new ()
{
    communicator_t c = malloc (sizeof (struct communicator_s));
    memset (c, 0, sizeof (struct communicator_s));

    c->id = lastId++;
    return c;
}

void communicator_setOnSuspiciousActivity(communicator_t c, SuspiciousFunc onSuspiciousActivity)
{
    c->onSuspiciousActivity = onSuspiciousActivity;
}

void communicator_setOnMessageReceived(communicator_t c, MessageReceivedFunc onMessageReceived)
{
    c->onMessageReceived = onMessageReceived;
}

int communicator_getId (communicator_t c)
{
    return c->id;
}

void communicator_free (communicator_t c)
{
    free (c);
}

char* communicator_getName (communicator_t c, char buffer[])
{
    strcpy (buffer, c->name);

    return buffer;
}

int communicator_setName (communicator_t c, const char* name)
{
    strcpy (c->name, name);

    return 0;
}

static void onCommunicatorMessageSending (communicator_t self,
                                          communicator_t receiver,
                                          communicator_t sender,
                                          const char* message)
{

    printf ("com %d informed that com %d has received message from com %d\n",
            self->id, receiver->id, sender->id);
    if (self == receiver)
    {
        receiver->onMessageReceived (receiver, message);
        sender->qMessages++;
    }

    if (sender->qMessages >= 10)
    {
        sender->onSuspiciousActivity (sender);
    }
}

MessageSendingFunc communicator_getCommunicatorMessageSending (communicator_t c)
{
    return &onCommunicatorMessageSending;
}
