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
        void fileWrite(char*);
        void fileClose();
    protected:
    private:
        std::ofstream* fileOut;
        int block;

};

#endif // CLIENTFILE_H
