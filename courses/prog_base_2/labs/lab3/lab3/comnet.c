#include "comnet.h"

struct comnet_s
{
    int q;
    event_t events[MAX_COMMUNICATOR];
};

comnet_t comnet_new ()
{
    comnet_t comnet = malloc (sizeof (struct comnet_s));
    memset (comnet, 0, sizeof (struct comnet_s));

    return comnet;
}

void comnet_subscribeMessageSending (comnet_t comnet, communicator_t c, void* callback)
{
    event_t event;
    event.self = c;
    event.callback = callback;
    comnet->events[ comnet->q++ ] = event;
}

void comnet_sendMessage (comnet_t comnet, communicator_t receiver, communicator_t sender, const char* message)
{
    for (int i = 0; i < comnet->q; i++)
        ((MessageSendingFunc)(comnet->events[i].callback))(comnet->events[i].self, receiver, sender, message);
}


void comnet_free (comnet_t comnet)
{
    free (comnet);
}
