#include "epoller.h"
#include <sys/epoll.h>
#include <iostream>
#include "channel.h"

#define EV_NUM 1024

EPoller::EPoller(const SocketAddress& addr)
{
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);
    
    int listen_fd = m_serv.getSocketHandle();
    m_epollfd = ::epoll_create1 (EPOLL_CLOEXEC);
    updateEpollCtl(EPOLL_CTL_ADD, &m_serv);
}

EPoller::~EPoller()
{
    for (auto client : m_clients)
    {
        delete client;
    }
    m_clients.clear();
    ::close(m_epollfd);
}

void EPoller::addPoll(const SocketAddress& addr)
{
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);
    
    int listen_fd = m_serv.getSocketHandle();
    m_epollfd = ::epoll_create1 (EPOLL_CLOEXEC);
    updateEpollCtl(EPOLL_CTL_ADD, &m_serv);

}

int EPoller::run(int interval)
{
    char buffer[1024];
    struct epoll_event evs[EV_NUM];
    int evnum = ::epoll_wait (m_epollfd, evs, EV_NUM, interval);
    int listen_fd = m_serv.getSocketHandle();
    for (int i = 0; i < evnum; ++i)
    {
        if (evs[i].data.ptr == &m_serv)
        {
            Socket* client = m_serv.accept();
            m_clients.push_back(client);
            updateEpollCtl(EPOLL_CTL_ADD, client);
        }
        else
        {
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

