#include "ClientSock.h"

ClientSock::ClientSock(std::string ser_name, int port_no)
{
    portNo = port_no;
    serName = ser_name;
    createSock();
}

//read something
std::string ClientSock::readIn(int size){
    char buffer[size];
    read(sockFd, buffer, size);
    std::string re(buffer);
    return re;
}

//write something
void ClientSock::writeOut(std::string toWrite){
    const char* c = toWrite.c_str();
    write(sockFd, c, strlen(c));
}

//opens and connects a new socket using the same ip and portno
void ClientSock::createSock(){
    //create socket
    sockFd = socket(AF_INET, SOCK_STREAM, 0);       //no clue what the constants mean

    //create server
    server = gethostbyname(serName.c_str());

    //test socket and server
    if(sockFd<0||!server)
        error("No such host");

    //connect socket to host ip and portno
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&serAddr.sin_addr.s_addr, server->h_length);
    //memcpy((char*)serAddr.sin_addr.s_addr , (char*)server->h_addr, server->h_length); //NOTE: s_addr is type unsigned int. dunno how it works tho
    serAddr.sin_port = htons(portNo);
    if(connect(sockFd, (struct sockaddr*)&serAddr, sizeof(serAddr))<0)
        error("Error connecting");

}

//closes current socket and opens a new one
void ClientSock::resetSock(){
    if(sockFd)
        close(sockFd);
    if(server)
        free(server);
    createSock();
}

//generic error message TO BE REWRITTEN
void ClientSock::error(std::string msg){
    std::cout << msg << std::endl;
    exit(1);                            //FORCE QUIT TO BE CHANGED
}

//destructor (pls no mem leaks)
ClientSock::~ClientSock()
{
    if(sockFd)
        close(sockFd);
    if(server)
        free(server);
}
