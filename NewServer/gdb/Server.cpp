#include "Server.h"
#include <unistd.h>
Server::Server(int port_no)
{
    portNo = port_no;
    newServer();
    //std::cout << "THIS PIECE OF SHIT DOESN'T WANT TO WORK" << std::endl;
    //testStuff();
    //testFileStuff();
    //sendFile("test1.txt");
    sendFile("/home/harry/DEW.png");
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
    std::cout << "# to send: " << (int)(fileIn->getSize()/BLOCK) << std::endl;
    for(c=0;c<(int)(fileIn->getSize()/BLOCK);c++){
        memset(buffer, 0, SIZE);
        fileIn->readBlock(buffer);
        //while(!sendInfo(buffer, BLOCK, c))
            sendInfo(buffer, BLOCK, c);//may need to add a counter to infinite loops
    }
    memset(buffer, 0, SIZE);
    fileIn->readLast(buffer);
    //while(!sendInfo(buffer, BLOCK, c))
        sendInfo(buffer,BLOCK,c);//may need anti infinite loops

    return true;
}

bool Server::sendInfo(const char* info, int len, int succ){
    char buffer[SIZE] = {0};
    char infobuffer[SIZE];
    strncpy(infobuffer, info, BLOCK);
    infobuffer[BLOCK] = '\0';
    usleep(10);
    if(server->writeOut(infobuffer, len)<0){      //send info
        return false;
    }
    usleep(10);
    if(server->readIn(buffer, len)<0){      //read the info back
        return false;
    }
    if(!strcmp(buffer, infobuffer)==0){           //check sent and read are equivalent
        //std::cout << "wrote: \n" << info << "\nread:\n" << buffer << std::endl;
        sprintf(buffer, "%07d", -1);
        //std::cout << buffer << std::endl;
        usleep(10);
        server->writeOut(buffer, 7);
        return false;
    }
    sprintf(buffer, "%07d", succ);
    usleep(10);
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
