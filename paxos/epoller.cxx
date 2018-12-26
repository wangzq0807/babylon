#include "epoller.h"
#include "channel.h"
#include <sys/epoll.h>
#include <iostream>

#define EV_NUM 1024

EPoller::EPoller()
{
    m_epollfd = ::epoll_create1 (EPOLL_CLOEXEC);
}

EPoller::~EPoller()
{
    m_channels.clear();
    ::close(m_epollfd);
}

void EPoller::addChannel(const ChannelPtr& channel)
{
    updateEpollCtl(EPOLL_CTL_ADD, channel);
}

void EPoller::removeChannel(const ChannelPtr& channel)
{
    updateEpollCtl(EPOLL_CTL_DEL, channel);
}

int EPoller::run(int interval)
{
    struct epoll_event evs[EV_NUM];
    int evnum = ::epoll_wait (m_epollfd, evs, EV_NUM, interval);
    for (int i = 0; i < evnum; ++i)
    {
        Channel* ptr = (Channel*)(evs[i].data.ptr);
        ptr->processEvent(evs[i].events);
    }
    return 0;
}

void EPoller::updateEpollCtl(int nflags, const ChannelPtr& channel)
{
    int fd = channel->getFd();
    struct epoll_event ev;
    ev.data.ptr = channel.get();
    ev.events = EPOLLIN | EPOLLET;
    ::epoll_ctl (m_epollfd, nflags, fd, &ev);
}

