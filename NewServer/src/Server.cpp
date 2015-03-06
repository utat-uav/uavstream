#include "Server.h"

Server::Server(char* ipAddress, int portNo)
{
    std::string temp(ipAddress);
    server = new ServerSock(temp, portNo);
    testStuff();
}

void Server::testStuff(){
    server->writeOut("havin' a giggle there m8?");
}

Server::~Server()
{
    delete server;
}
