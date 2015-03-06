#include "Client.h"

Client::Client(char* ipAddress, int portNo)
{
    std::string temp(ipAddress);
    client = new ClientSock(temp, portNo);
    testStuff();
}

void Client::testStuff(){
    std::string temp = client->readIn(BLOCK);
    std::cout << temp << std::endl;
}

Client::~Client()
{
    delete client;
}
