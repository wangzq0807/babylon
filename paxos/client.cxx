#include <string.h>
#include <iostream>
#include <unistd.h>
#include "socket.h"

using namespace std;

#define SERV_PORT 5566
#define BUF_SIZE 1024

int main(int argc, const char* argv[])
{
    char msg[BUF_SIZE] = "Hello, World!";
    SocketAddress servAddr(SERV_PORT);
    Socket conn;
    try
    {
        conn.connect(servAddr);
    }
    catch(exception e)
    {
        cout << "conn failed" << endl;
        return 0;
    }

    while (1)
    {
        int ret = conn.send(msg, BUF_SIZE);
        cout << ret << msg << endl;
    }
    return 0;
}
