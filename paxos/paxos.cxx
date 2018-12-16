#include <iostream>
#include "socket.h"
#include "epoller.h"

using namespace std;

int main(int argc, const char* argv[])
{
    cout << "hello, paxos!" << endl;
    SocketAddress addr(5566);
    //run_server (5566);

    return 0;
}
