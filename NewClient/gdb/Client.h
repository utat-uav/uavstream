#ifndef CLIENT_H
#define CLIENT_H
#include "ClientSock.h"
#include "ClientFile.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed
#include <unistd.h>

#define BLOCK 2048

class Client
{
    public:
        Client(std::string server_name, int port_number);
        virtual ~Client();
    protected:
    private:
        ClientSock* client;
        ClientFile* fileOut;
        std::string serName;
        int portNo;

        void newClient();
        void testStuff();
        void newFile();
        void testFileStuff();
};

#endif // CLIENT_H
