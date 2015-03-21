#ifndef SERVER_H
#define SERVER_H

#include "ServerSock.h"
#include "ServerFile.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed

#define BLOCK 2048

class Server
{
    public:
        Server(int port_number);
        virtual ~Server();
    protected:
    private:
        ServerSock* server;
        ServerFile* fileIn;
        int portNo;

        void newServer();
        void testStuff();
        void newFile();
        void testFileStuff();
};

#endif // SERVER_H
