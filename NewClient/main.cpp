#include <iostream>
#include "Client.h"

using namespace std;

int main()
{
    Client* test = new Client("localhost", 5914);
    cout << "ending normally" << endl;
    //delete test; //don't know why but it's bugging out
    return 0;
}
