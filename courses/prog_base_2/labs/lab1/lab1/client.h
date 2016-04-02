#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

typedef struct tagClient_Private Client_Private;

typedef struct
{
    Client_Private* cp;
} Client;

int Client_initialize (Client*, int);
int Client_deinitialize (Client*);

int Client_getId (Client*);
int Client_getSeatState (Client*);

int Client_getMaxSeat (Client*);

int Client_getAction (Client*, int*, int*);

char* Client_errorCode_toString (int);

#endif // CLIENT_H_INCLUDED
