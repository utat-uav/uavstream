#include "Server.h"
#include <unistd.h>
Server::Server(int port_no)
{
    portNo = port_no;
    newServer();
    //testStuff();
    //testFileStuff();
    sendFile("test1.txt");
    //sendFile("/home/harry/SABAH.jpg");
    server->writeOut("E");
}

bool Server::sendFile(std::string file_path){
    //test connection
    if(!server->isConnected()){
        return false;
    }

    //open and test file
    if(fileIn!=NULL){
        delete fileIn;
        fileIn = NULL;
    }
    fileIn = new ServerFile(file_path, BLOCK);
    if(!fileIn->isOpen()){
        return false;
    }

    //send file name and size
    char buffer[SIZE] = {0};
    server->writeOut("F", 1);
    server->readIn(buffer, 1);
    sendInfo(fileIn->getName().c_str(), BLOCK, 0);      //add handling later
    sprintf(buffer, "%d", (int)fileIn->getSize());      //change to unsigned later
    sendInfo(buffer, BLOCK, 0);

    int c;
    for(c=0;c<(int)(fileIn->getSize()%BLOCK);c++){
        memset(buffer, 0, SIZE);
        fileIn->readBlock(buffer);
        std::cout << "writing block #" << c << std::endl;
        std::cout << buffer << std::endl;
        while(!sendInfo(buffer, BLOCK, c))
            usleep(5000000);//may need to add a counter to infinite loops
        if(c<10){
            std::cout << c << "\b";
        }else if(c<100){
            std::cout << c << "\b\b";
        }else if(c<1000){
            std::cout << c << "\b\b\b";
        }else if(c<10000){
            std::cout << c << "\b\b\b\b";
        }
        std::cout << "wrote block #" << c << std::endl;
        usleep(5000000);
    }
    memset(buffer, 0, SIZE);
    fileIn->readLast(buffer);
    while(!sendInfo(buffer, BLOCK, c))
        ;//may need anti infinite loops

    return true;
}

bool Server::sendInfo(const char* info, int len, int succ){
    char buffer[SIZE] = {0};
    if(server->writeOut(info, len)<0){      //send info
        return false;
    }
    if(server->readIn(buffer, len)<0){      //read the info back
        return false;
    }
    if(!strcmp(buffer, info)==0){           //check sent and read are equivalent
        //std::cout << "wrote: \n" << info << "\nread:\n" << buffer << std::endl;
        sprintf(buffer, "%07d", -1);
        //std::cout << buffer << std::endl;
        server->writeOut(buffer, 7);
        return false;
    }
    sprintf(buffer, "%07d", succ);
    server->writeOut(buffer, 7);
    return true;
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
        fPath = fileIn->getName();
        server->writeOut(fPath.c_str());
        std:: cout << "wrote file name: " << fPath << std::endl;
        memset(buffer, 0, BLOCK+1);
        sprintf(buffer, "%d", (int)fileIn->getSize());
        server->writeOut(buffer);
        std::cout << "wrote file size: " << buffer << std::endl;
        for(int c=(int)(fileIn->getSize()/BLOCK);c>0;c--){
            fileIn->readBlock(buffer);
            server->writeOut(buffer, BLOCK);
        }
        fileIn->readLast(buffer);
        server->writeOut(buffer, (int)(fileIn->getSize()%BLOCK));
    }else{
        std::cout << "file does not exist" << std::endl;
    }
    delete fileIn;
}

Server::~Server()
{
    delete server;
}
