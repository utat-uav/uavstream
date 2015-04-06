#ifndef CLIENT_H
#define CLIENT_H
#include "ClientSock.h"
#include "ClientFile.h"

#include <string.h>
#include <fstream>
#include <string>
#include <iostream> //to be removed
#include <unistd.h>

#define SIZE 2048
#define BLOCK SIZE/2

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
        void handleInput();
        int readInfo(char* info, int length);
        void recvFile(unsigned int file_size);
        void newFile(const char* file_path);
        void testStuff();
        void testFileStuff();
};

#endif // CLIENT_H
