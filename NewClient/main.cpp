#include <iostream>
#include "include/Client.h"

using namespace std;

int main()
{
    Client* test = new Client("localhost", 5914);
    cout << "ending normally" << endl;
    delete test;
    return 0;
}
