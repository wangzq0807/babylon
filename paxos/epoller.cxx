#include "epoller.h"
#include <sys/epoll.h>
#include <iostream>

#define EV_NUM 20

EPoller::EPoller(unsigned short port)
{
    SocketAddress addr(port);
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);
    
    int listen_fd = m_serv.getSocketHandle();
    m_epollfd = ::epoll_create1 (EPOLL_CLOEXEC);
    updateEpollCtl(EPOLL_CTL_ADD, &m_serv);
}

EPoller::~EPoller()
{
    for (auto conn : m_conns)
    {
        delete conn;
    }
    m_conns.clear();
    ::close(m_epollfd);
}

int EPoller::run(int timeout)
{
    char buffer[1024];
    struct epoll_event evs[EV_NUM];
    int evnum = ::epoll_wait (m_epollfd, evs, EV_NUM, timeout);
    int listen_fd = m_serv.getSocketHandle();
    for (int i = 0; i < evnum; ++i)
    {
        if (evs[i].data.ptr == &m_serv)
        {
            Socket* conn = m_serv.accept();
            m_conns.push_back(conn);
            updateEpollCtl(EPOLL_CTL_ADD, conn);
        }
        else
        {
            Socket* conn = static_cast<Socket *>(evs[i].data.ptr);
            int read_num = conn->receive(buffer, 1024, 0);
            if (read_num)
            {
                std::cout << buffer << std::endl;
                //auto itr = find(conn_fds.begin(), conn_fds.end(), connfd);
            }
            else
            {
                //cout << buffer << endl;
            }
        }
    }
    return 0;
}

void EPoller::updateEpollCtl(int nflags, SocketBase* socket)
{
    int fd = socket->getSocketHandle();
    struct epoll_event ev;
    ev.data.ptr = socket;
    ev.events = EPOLLIN | EPOLLET;
    ::epoll_ctl (m_epollfd, nflags, fd, &ev);
}

