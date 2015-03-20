#ifndef SERVERSOCK_H
#define SERVERSOCK_H

#include <iostream> //debugging purposes

#include <cstdlib>
#include <netdb.h>        //may or may not be necessary
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>       //may or may not be necessary

class ServerSock
{
    public:
        ServerSock(int);
        virtual ~ServerSock();

        //public functions
        std::string readIn(int);
        void writeOut(std::string);
        bool isConnected();
    protected:
    private:
        //private global variables
        int sockFd, newsockFd;
        struct sockaddr_in serAddr, cliAddr;

        int portNo;
        bool connected;

        //private functions
        bool createSock();
        void error(std::string);

};

#endif // SERVERSOCK_H
