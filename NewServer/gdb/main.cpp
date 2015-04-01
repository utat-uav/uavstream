#include <iostream>

#include "Server.h"

using namespace std;

int main()
{
    Server* test = new Server(5914);
    cout << "ending normally" << endl;
    delete test;
    return 0;
}
