#include "Server.h"

Server::Server(int port_no)
{
    portNo = port_no;
    newServer();
    testStuff();
}

void Server::newServer(){
    do{
        if(server!=NULL){
            delete server;
            server = NULL;
        }
        server = new ServerSock(portNo);
        if(!server->isConnected()){
            std::cout << "binding failed" << std::endl;
            usleep(1000000);
        }
    }while(!server->isConnected());
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
            newServer();
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
