#ifndef SERVER_H
#define SERVER_H

#include "ServerSock.h"
#include "ServerFile.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed

#define SIZE 2048
#define BLOCK SIZE/2

class Server
{
    public:
        Server(int port_number);
        virtual ~Server();
        bool sendFile(std::string file_path);
    protected:
    private:
        ServerSock* server;
        ServerFile* fileIn;
        int portNo;

        bool sendInfo(const char* info, int length, int successful);
        void newServer();
        void testStuff();
        void newFile();
        void testFileStuff();
};

#endif // SERVER_H
