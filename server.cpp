#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define BLOCK 1024

void error(string msg){
    cerr << msg << endl;
    exit(0);
}

void getName(char* fpathstart){
    int offset = 0;
    char* ptr = fpathstart;
    for(int c = 0; *ptr; c++, ptr++)
        if(*ptr=='/')
            offset = c+1;
    while((*fpathstart=*(fpathstart+offset)))fpathstart++;
}

int main()
{
    //declarations
    int sockfd, newsockfd, portno, clilen;
    char buffer[BLOCK];
    struct sockaddr_in serv_addr, cli_addr;
    //file declarations
    int fSize;
    char fName[256];

    //create input stream
    cout << "Path to file: ";
    cin >> fName;
    ifstream fileI(fName, ios::ate|ios::binary);
    if(!fileI.is_open())
        error("file not found");

    //create and test socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
        error("Error opening socket");

    //create port
    cout << "port number (2000-65535): ";
    cin >> portno;

    //bind socket to specified port
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
        error("Error on binding");

    //wait for client to connect
    cout << "listening" << endl; //remove
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, (socklen_t*)&clilen);
    if(newsockfd<0)
        error("Error on accept");

    //send file size and name
    cout << "sending file size" << endl;
    bzero(buffer, BLOCK);
    sprintf(buffer, "%d", fSize=(int)fileI.tellg());
    if(write(newsockfd, buffer, strlen(buffer))<0)
        error("Error sending size");
    read(newsockfd, buffer, 255);
    cout << "sending file name" << endl;
    getName(fName);
    if(write(newsockfd, fName, strlen(fName))<0)
        error("Error sending name");
    read(newsockfd, buffer, 255);

    //send file info to client
    fileI.seekg(0, ios::beg);
    int c; //future error handling?
    for(c=fSize/BLOCK;c>0;c--){
        fileI.read(buffer, BLOCK);
        if(write(newsockfd, buffer, BLOCK)<0)
            error("error writing block");
        if(read(newsockfd, buffer, BLOCK)<0)
            error("error reading block");
    }
    fileI.read(buffer, BLOCK);
    if(write(newsockfd, buffer, fSize%BLOCK)<0)
        error("error writing last block");
    if(read(newsockfd, buffer, fSize%BLOCK)<0)
        error("error reading last block");
    fileI.close();

    //finished tasks
    close(sockfd);
    close(newsockfd);
    cout << "tasks completed successfully" << endl;
    return 0;
}
