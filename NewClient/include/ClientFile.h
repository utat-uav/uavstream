#ifndef CLIENTFILE_H
#define CLIENTFILE_H

#include <fstream>
#include <iostream>

class ClientFile
{
    public:
        ClientFile(std::string file_name);
        virtual ~ClientFile();

        //open, write, close
        void fileOpen(std::string);
        void fileWrite(char*, int len);
        void fileClose();
        bool isDuplicate(std::string);
        std::string getName();
    protected:
    private:
        std::ofstream* fileOut;
        int block;
        unsigned int fSize;
        unsigned int fLeft;
        std::string fName;

};

#endif // CLIENTFILE_H
