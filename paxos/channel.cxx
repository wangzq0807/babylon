#include "channel.h"
#include "eventloop.h"
#include <sys/epoll.h>
#include <assert.h>
#include <iostream>

Channel::Channel()
    :m_events(0),
    m_fd(-1),
    m_loop(nullptr)
{}

Channel::~Channel()
{
}

void Channel::processEvent(unsigned int events)
{
    m_events = events;
    if (m_events & (EPOLLIN | EPOLLRDHUP | EPOLLPRI))
    {
        onRead();
    }
}

void Channel::addToLoop(EventLoop* loop)
{
    assert(m_loop == nullptr);
    assert(loop != nullptr);
    loop->addChannel(shared_from_this());
    m_loop = loop;
}

void Channel::removeFromLoop()
{
    assert(m_loop != nullptr);
    m_loop->removeChannel(shared_from_this());
    m_loop = nullptr;
}

void Channel::onRead()
{}

void Channel::onWrite()
{}

void Channel::onClose()
{}

void Channel::onError()
{}

