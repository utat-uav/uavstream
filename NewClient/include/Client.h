#ifndef CLIENT_H
#define CLIENT_H
#include "ClientSock.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed
#include <unistd.h>

#define BLOCK 2048

class Client
{
    public:
        Client(std::string, int);
        virtual ~Client();
    protected:
    private:
        ClientSock* client;
        std::string serName;
        int portNo;

        void newClient();
        void testStuff();
};

#endif // CLIENT_H
