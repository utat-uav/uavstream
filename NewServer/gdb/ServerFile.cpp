#include "ServerFile.h"

ServerFile::ServerFile(std::string file_path, int block_size)
{
    fName = file_path.substr(file_path.rfind('/')+1);
    block = block_size;
    fileIn = new std::ifstream(file_path.c_str(), std::ios::binary | std::ios::ate);
    if(fileIn->is_open()){
        fSize = (unsigned int)fileIn->tellg();
        reset();
    }else{
        fSize = 0;
    }
}

void ServerFile::readBlock(char* s){
    memset(s, 0, block+1);
    fileIn->read(s, ((unsigned int)block>fLeft)?block:fLeft);
    fLeft -= (unsigned int)block;
}

void ServerFile::readLast(char* s){
    memset(s, 0, fLeft+1);
    fileIn->read(s, fLeft);
}

void ServerFile::reset(){
    fLeft = fSize;
    fileIn->seekg(0, std::ios::beg);
}

std::string ServerFile::getName(){
    return fName;
}

unsigned int ServerFile::getSize(){
    return fSize;
}

bool ServerFile::isOpen(){
    return fileIn->is_open()&&fLeft>0;
}

ServerFile::~ServerFile()
{
    fileIn->close();
    delete fileIn;
}
