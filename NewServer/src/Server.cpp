#include "Server.h"

Server::Server(char* ipAddress, int portNo)
{
    std::string temp(ipAddress);
    server = new ServerSock(temp, portNo);
    testStuff();
}

void Server::testStuff(){
    bool ending = false;
    std::string input, cliIn;
    while(!ending){
        std::cout << ">>";
        std::cin >> input;
        if(input=="R"){
            server->writeOut("R");
            cliIn = server->readIn(8);
            std::cout << "Response: " << cliIn << std::endl;
            server->resetSock();
            std::cout << "Server reset" << std::endl;
        }else if(input == "End"){
            server->writeOut("End");
            cliIn = server->readIn(8);
            std::cout << "Response: " << cliIn << std::endl;
            ending = true;
        }
        else{
            server->writeOut(input);
            cliIn = server->readIn(8);
            std::cout << "Response: " << cliIn << std::endl;
        }
    }
}

Server::~Server()
{
    delete server;
}
