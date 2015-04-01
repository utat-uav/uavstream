#ifndef SERVERFILE_H
#define SERVERFILE_H

#include <iostream>
#include <fstream>
#include <string.h>

class ServerFile
{
    public:
        ServerFile(std::string file_path, int buffer_size);
        virtual ~ServerFile();

        //public functions
        std::string getName();
        unsigned int getSize();
        bool isOpen();
        void readBlock(char*);
        void readLast(char*);
        void reset();
    protected:
    private:
        //private global variables
        std::ifstream* fileIn;
        unsigned int fSize;
        unsigned int fLeft;
        std::string fName;
        int block;
};

#endif // SERVERFILE_H
