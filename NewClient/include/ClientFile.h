#ifndef CLIENTFILE_H
#define CLIENTFILE_H

#include <fstream>
#include <iostream>

class ClientFile
{
    public:
        ClientFile(int, std::string);
        virtual ~ClientFile();
        //open, write, close
        void fileOpen(std::string);
        void fileWrite(std::string);
    protected:
    private:
        std::ofstream* file;
};

#endif // CLIENTFILE_H
