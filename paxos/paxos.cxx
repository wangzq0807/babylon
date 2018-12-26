#include <iostream>
#include "eventloop.h"
#include "tcpserver.h"
#include "tcpconnection.h"
using namespace std;

void onMessage(TcpConnectionPtr conn)
{
}

int main(int argc, const char* argv[])
{
    cout << "hello, paxos!" << endl;
    EventLoop loop;
    TcpServer serv(&loop, 5566);
    serv.setMessageCallback(std::bind(onMessage, std::placeholders::_1));
    loop.run();
    //run_server (5566);

    return 0;
}
