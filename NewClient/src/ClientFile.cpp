#include "ClientFile.h"
#include <string.h>

ClientFile::ClientFile(std::string fileName)
{
    //ctor
    char i = '1';
    while (isDuplicate(fileName)){
        std::string temp(1,i);
        fileName = fileName.substr(0, fileName.find(".")-1) + temp + fileName.substr(fileName.find("."), fileName.length()-fileName.find("."));
        i++;
    }
    fileOpen(fileName);
}

void ClientFile::fileOpen(std::string fName){
    fileOut = new std::ofstream();
    const char* c = fName.c_str();
    fileOut->open(c, std::ios::binary);
}

void ClientFile::fileWrite(char* s){
    block = strlen(s);
    fileOut->write(s,block);
}

void ClientFile::fileClose(){
    fileOut->close();
}

bool ClientFile::isDuplicate(std::string filename){
    std::ifstream testStream = new std::ifstream(filename.c_str());
    if (testStream->is_open()){
        testStream->close();
        return true;
    }
    else{
        testStream->close();
        return false;
    }
}

ClientFile::~ClientFile()
{
    //dtor
    fileClose();
    delete fileOut;
}
