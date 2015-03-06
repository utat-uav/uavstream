#include <iostream>

#include "Server.h"

using namespace std;

int main()
{
    Server* test = new Server("localhost", 5914);
    cout << "ending normally" << endl;
    return 0;
}
