#include <iostream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "socket.h"

using namespace std;
using namespace phxpaxos;

int epoll_fd = -1;
vector<int> conn_fds;

void epoll_add(int epoll_fd, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}

int
run_server (int port)
{
    SocketAddress servAddr(port);
    ServerSocket serv;
    serv.setNonBlocking(true);
    serv.listen(servAddr);

    int listen_fd = serv.getSocketHandle();

    // epoll listen_fd
    epoll_fd = epoll_create (1);
    epoll_add(epoll_fd, listen_fd);

    char buffer[1024 + 1];
    struct epoll_event evs[20];
    while (true)
    {
        int tnum = epoll_wait (epoll_fd, evs, 20, 500);
        for (int i = 0; i < tnum; ++i)
        {
            if (evs[i].data.fd == listen_fd)
            {
                Socket* conn =  serv.accept();
                int conn_fd = conn->getSocketHandle();
                epoll_add(epoll_fd, conn_fd);
            }
            else
            {
                int connfd = evs[i].data.fd;
                size_t read_num = recv(connfd, buffer, 1024, 0);
                if (read_num)
                {
                    cout << buffer << endl;
                    //auto itr = find(conn_fds.begin(), conn_fds.end(), connfd);
                }
                else
                {
                    cout << buffer << endl;
                }
            }
        }
    }
}

int main(int argc, const char* argv[])
{
    cout << "hello, paxos!" << endl;
    run_server (5566);

    return 0;
}
