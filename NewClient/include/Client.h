#ifndef CLIENT_H
#define CLIENT_H
#include "ClientSock.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed

#define BLOCK 2048

class Client
{
    public:
        Client(char*, int);
        virtual ~Client();
    protected:
    private:
        ClientSock* client;
        void testStuff();
};

#endif // CLIENT_H
