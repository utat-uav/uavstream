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

int main()
{
    //declarations
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[BLOCK];
    //file IO declarations
    int fSize;
    char fName[256];

    //get ip and port number
    cout << "Server IP: ";
    memset(fName, 0, 256);
    cin >> fName;
    server = gethostbyname(fName);
    memset(fName, 0, 256);
    cout << "Port number: ";
    cin >> fName;
    portno = atoi(fName);
    memset(fName, 0, 256);

    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //test if socket and server exist
    if(sockfd<0)
        error("Error opening socket");
    if(!server){
        cout<< "No such host" << endl;
        exit(0);
    }

    //ok I give up now
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
        error("Error connecting");

    //read file size and name
    if(read(sockfd, buffer, BLOCK)<0)
        error("Error reading size");
    fSize = atoi(buffer);
    cout << fSize << " bytes" << endl; //remove
    if(write(sockfd, buffer, strlen(buffer))<0)
        error("Error confirming size");
    if(read(sockfd, fName, 256)<0)
        error("Error reading name");
    cout << fName << endl;
    if(write(sockfd, fName, strlen(fName))<0)
        error("Error confirming size");

    //open output filestream
    ofstream fileO(fName, ios::binary);
    int c; //future error handling?
    for(c=fSize/BLOCK;c>0;c--){
        if(read(sockfd, buffer, BLOCK)<0)
            error("error reading block");
        fileO.write(buffer, BLOCK);
        if(write(sockfd, buffer, BLOCK)<0)
            error("error writing block");
    }
    memset(buffer, 0, BLOCK);
    if(read(sockfd, buffer, fSize%BLOCK)<0)
        error("error reading last block");
    fileO.write(buffer, fSize%BLOCK);
    if(write(sockfd, buffer, fSize%BLOCK)<0)
        error("error writing last block");

    //close socket
    close(sockfd);
    return 0;
}
