#ifndef COMNET_H_INCLUDED
#define COMNET_H_INCLUDED

#include "event.h"
#include "communicator.h"

#define MAX_COMMUNICATOR 10

#include "communicator.h"

typedef struct comnet_s* comnet_t;

comnet_t comnet_new ();

void comnet_subscribeMessageSending(comnet_t, communicator_t, void*);
void comnet_sendMessage ( comnet_t, communicator_t, communicator_t, const char* );

void comnet_free (comnet_t);

#endif // COMNET_H_INCLUDED
