#include "ServerSock.h"

ServerSock::ServerSock(std::string ser_name, int port_no)
{
    portNo = port_no;
    serName = ser_name;
    createSock();
}

//read something
std::string ServerSock::readIn(int size){
    char buffer[size];
    memset(buffer, 0, size);
    read(newsockFd, buffer, size);
    std::string re(buffer);
    return re;
}

//write something
void ServerSock::writeOut(std::string toWrite){
    const char* c = toWrite.c_str();
    write(newsockFd, c, strlen(c));
}

//open server socket and client socket
void ServerSock::createSock(){
    //create and test socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd<0)
        error("Error opening socket");

    //bind socket to port
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = INADDR_ANY;
    serAddr.sin_port = htons(portNo);
    if(bind(sockFd, (struct sockaddr*)&serAddr, sizeof(serAddr))<0)
        error("Error on binding");

    //wait for client to connect
    std::cout << "listening" << std::endl;
    listen(sockFd, 5);
    int clilen = sizeof(cliAddr);
    newsockFd = accept(sockFd, (struct sockaddr*)&cliAddr, (socklen_t*)&clilen);
    if(newsockFd<0)
        error("Error on accept");
}

//closes sockets and reopens them
void ServerSock::resetSock(){
    if(sockFd>=0)
        close(sockFd);
    if(newsockFd>=0)
        close(newsockFd);
    createSock();
}

//generic error TO BE REWRITTEN
void ServerSock::error(std::string msg){
    std::cout << msg << std::endl;
    exit(1);                            //FORCE QUIT TO BE CHANGED
}

//deconstructor pls no mem leaks
ServerSock::~ServerSock()
{
    if(sockFd)
        close(sockFd);
    if(newsockFd)
        close(newsockFd);
}
