#include <iostream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int listen_fd = -1;
int epoll_fd = -1;
vector<int> conn_fds;

void
set_nonblocking (int fd)
{
    int flags = fcntl (fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl (fd, F_SETFL, flags);
}

int
run_server (int port)
{
    listen_fd = socket (AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    bzero (&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
    server_addr.sin_port = htons (port);

    bind (listen_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    set_nonblocking (listen_fd);

    epoll_fd = epoll_create (20);
    struct epoll_event ev;
    ev.data.fd = listen_fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl (epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);

    listen (listen_fd, 1024);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    char buffer[1024 + 1];
    struct epoll_event evs[20];
    while (true)
    {
        int tnum = epoll_wait (epoll_fd, evs, 20, 500);
        for (int i = 0; i < tnum; ++i)
        {
            if (evs[i].data.fd == listen_fd)
            {
                int connfd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
                conn_fds.push_back (connfd);
            }
            else
            {
                int connfd = evs[i].data.fd;
                size_t read_num = recv(connfd, buffer, 1024, 0);
                if (read_num)
                {
                    auto itr = find(conn_fds.begin(), conn_fds.end(), connfd);
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
