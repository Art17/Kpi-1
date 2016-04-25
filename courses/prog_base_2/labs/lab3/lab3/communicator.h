#ifndef COMUNICATOR_H_INCLUDED
#define COMUNICATOR_H_INCLUDED

typedef struct communicator_s* communicator_t;
typedef int (*SuspiciousFunc)(communicator_t);
typedef int (*MessageReceivedFunc)(communicator_t, const char*);
typedef void (*MessageSendingFunc)(communicator_t, communicator_t, communicator_t, const char*);

communicator_t communicator_new ();
int communicator_getId (communicator_t);

char* communicator_getName (communicator_t, char []);
int communicator_setName (communicator_t, const char*);

void communicator_setOnSuspiciousActivity (communicator_t,  SuspiciousFunc );
void communicator_setOnMessageReceived (communicator_t,  MessageReceivedFunc );

MessageSendingFunc communicator_getCommunicatorMessageSending (communicator_t);

void communicator_free ();

#endif // COMUNICATOR_H_INCLUDED
