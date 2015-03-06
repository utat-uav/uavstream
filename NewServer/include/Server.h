#ifndef SERVER_H
#define SERVER_H

#include "ServerSock.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed

class Server
{
    public:
        Server(char*,  int);
        virtual ~Server();
    protected:
    private:
        ServerSock* server;
        void testStuff();
};

#endif // SERVER_H
