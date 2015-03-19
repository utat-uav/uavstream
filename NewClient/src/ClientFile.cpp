#include "ClientFile.h"
#include <string.h>

ClientFile::ClientFile(int, std::string)
{
    //ctor
}

ClientFile::~ClientFile()
{
    //dtor
}

void ClientFile::fileOpen(std::string fName){
    file = new std::ofstream();
    const char* c = fName.c_str();
    file->open(c);
}

void ClientFile::fileWrite(std::string memBlock){
    if (file.is_open()){
        int inputSize = strlen(memBlock);
        file.write(memBlock, inputSize);
        std::cout << "writing to client file";
    }
    else{
        std::cout << "unable to open file";
    }
}
