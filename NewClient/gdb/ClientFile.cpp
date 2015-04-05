#include "ClientFile.h"
#include <string.h>

ClientFile::ClientFile(std::string fileName)
{
    //ctor
    int i = 1;
    while (isDuplicate(fileName)){
        int hmm = 0; //1st copy = 0, 2nd copy = 1, 11th copy = 2, 101th copy = 3
        std::string temp = ""+i;
        if (i==1)
            hmm=0;
        else if (i<11)
            hmm=1;
        else if (i<101)
            hmm=2;
        else
            hmm=3;
        fileName = fileName.substr(0, fileName.find(".")-hmm) + temp + fileName.substr(fileName.find("."), fileName.length()-fileName.find("."));
        i++;
    }
    fName = fileName;
    fileOpen(fileName);
}

std::string ClientFile::getName(){
    return fName;
}

void ClientFile::fileOpen(std::string fName){
    fileOut = new std::ofstream();
    const char* c = fName.c_str();
    fileOut->open(c, std::ios::binary);
}

void ClientFile::fileWrite(char* s, int len){
    fileOut->write(s, len);
}

void ClientFile::fileClose(){
    fileOut->close();
}

bool ClientFile::isDuplicate(std::string filename){
    std::ifstream* testStream = new std::ifstream(filename.c_str());
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
