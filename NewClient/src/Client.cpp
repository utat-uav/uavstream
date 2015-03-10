#include "Client.h"

Client::Client(char* ipAddress, int portNo)
{
    std::string temp(ipAddress);
    client = new ClientSock(temp, portNo);
    testStuff();
}

void Client::testStuff(){
    bool ending = false;
    std::string serIn;
    while(!ending){
        serIn = client->readIn(BLOCK);
        if(serIn == "R"){
            client->writeOut("RC");
            client->resetSock();
            std::cout << "Client reset" << std::endl;
        }else if(serIn == "End"){
            client->writeOut("EndC");
            ending = true;
        }else{
            std::cout << serIn << std::endl;
            client->writeOut("read");
        }
    }
}

Client::~Client()
{
    delete client;
}
