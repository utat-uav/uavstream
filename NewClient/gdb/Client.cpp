#include "Client.h"

Client::Client(std::string ser_name, int port_no)
{
    serName = ser_name;
    portNo = port_no;
    newClient();
    //testStuff();
    testFileStuff();
}

void Client::newClient(){
    do{
        if(client!=NULL){
            delete client;
            client = NULL;
        }
        client = new ClientSock(serName, portNo);
        if(!client->isConnected()){
            std::cout << "reconnecting..." << std::endl;
            usleep(1000000);
        }
    }while(!client->isConnected());
}

void Client::testStuff(){
    bool ending = false;
    std::string serIn;
    while(!ending){
        serIn = client->readIn(BLOCK);
        if(serIn == "R"){
            client->writeOut("RC");
            newClient();
            std::cout << "Client reset" << std::endl;
        }else if(serIn == "End"){
            client->writeOut("EndC");
            ending = true;
        }else{
            std::cout << serIn << std::endl;
            client->writeOut("read");
        }
    }
}

void Client::newFile(){

}

void Client::testFileStuff(){
    char buffer[BLOCK+1];
    unsigned int fSize;

    client->readIn(buffer, BLOCK);
    fSize = (unsigned int)atoll(buffer);
    client->readIn(buffer, BLOCK);
    std::string fName(buffer);
    fileOut = new ClientFile(fName);
    std::cout << fSize << " " << fName << std::endl;
    for(int c=(int)(fSize/BLOCK);c>0;c--){
        client->readIn(buffer, BLOCK);
        fileOut->fileWrite(buffer);
        std::cout << "wrote " << c << std::endl;
    }
    client->readIn(buffer, (int)(fSize%BLOCK));
    fileOut->fileWrite(buffer);
}

Client::~Client()
{
    delete client;
}
