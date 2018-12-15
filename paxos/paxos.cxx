#include <iostream>
#include "socket.h"
#include "epoller.h"

using namespace std;

int main(int argc, const char* argv[])
{
    cout << "hello, paxos!" << endl;
    EPoller ep(5566);
    while (true)
        ep.run(500);
    //run_server (5566);

    return 0;
}
