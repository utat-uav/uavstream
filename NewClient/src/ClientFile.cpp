#include "ClientFile.h"
#include <string.h>

ClientFile::ClientFile(std::string fileName)
{
    //ctor
    fileOpen(fileName);
}

void ClientFile::fileOpen(std::string fName){
    fileOut = new std::ofstream();
    const char* c = fName.c_str();
    fileOut->open(c, std::ios::out|std::ios::binary);
}

void ClientFile::fileWrite(char* s){
    block = strlen(s);
    fileOut->write(s,block);
}

void ClientFile::fileClose(){
    fileOut->close();
}

ClientFile::~ClientFile()
{
    //dtor
    fileClose();
    delete fileOut;
}
