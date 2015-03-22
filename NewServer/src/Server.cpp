#include "Server.h"

Server::Server(int port_no)
{
    portNo = port_no;
    newServer();
    //testStuff();
    testFileStuff();
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
            usleep(10000000); //10 seconds
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

void Server::newFile(){

}

void Server::testFileStuff(){
    std::string fPath;
    std::cout << "File path: ";
    std::cin >> fPath;
    char buffer[BLOCK+1];
    fileIn = new ServerFile(fPath, BLOCK);
    if(fileIn->isOpen()){
        server->writeOut(fPath.c_str());
        std:: cout << "wrote file name: " << fPath << std::endl;
        memset(buffer, 0, BLOCK+1);
        sprintf(buffer, "%d", (int)fileIn->getSize());
        server->writeOut(buffer);
        std::cout << "wrote file size: " << buffer << std::endl;
        for(int c=(int)(fileIn->getSize()/BLOCK);c>0;c--){
            fileIn->readBlock(buffer);
            server->writeOut(buffer);
            //std::cout << "wrote " << buffer << std::endl;
        }
        fileIn->readLast(buffer);
        server->writeOut(buffer);
        //std::cout << "wrote " << buffer << std::endl;
    }else{
        std::cout << "file does not exist" << std::endl;
    }
}

Server::~Server()
{
    delete server;
}
