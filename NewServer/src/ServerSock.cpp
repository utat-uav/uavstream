#include "ServerSock.h"

ServerSock::ServerSock(int port_no)
{
    portNo = port_no;
    connected = createSock();
}

//read something
std::string ServerSock::readIn(int size){
    char buffer[size];
    memset(buffer, 0, size);
    read(newsockFd, buffer, size);
    std::string re(buffer);
    return re;
}

int ServerSock::readIn(char* s, int i){
    memset(s, 0, i+1);
    return read(newsockFd, s, i);
}

//write something
void ServerSock::writeOut(std::string toWrite){
    const char* c = toWrite.c_str();
    write(newsockFd, c, strlen(c));
}

int ServerSock::writeOut(const char* toWrite){
    return write(newsockFd, toWrite, strlen(toWrite));
}

//open server socket and client socket
bool ServerSock::createSock(){
    //create and test socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFd<0)
        return false;

    //bind socket to port
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = INADDR_ANY;
    serAddr.sin_port = htons(portNo);
    if(bind(sockFd, (struct sockaddr*)&serAddr, sizeof(serAddr))<0)
        return false;

    //wait for client to connect
    std::cout << "listening" << std::endl;
    listen(sockFd, 5); //5 is backlog
    int clilen = sizeof(cliAddr);
    newsockFd = accept(sockFd, (struct sockaddr*)&cliAddr, (socklen_t*)&clilen);
    if(newsockFd<0)
        return false;

    return true;
}

bool ServerSock::isConnected(){
    return connected;
}

//deconstructor pls no mem leaks
ServerSock::~ServerSock()
{
    if(sockFd>=0)
        close(sockFd);
    if(newsockFd>=0)
        close(newsockFd);
}
