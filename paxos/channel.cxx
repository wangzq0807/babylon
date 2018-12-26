#include "channel.h"
#include "eventloop.h"
#include <sys/epoll.h>
#include <assert.h>

Channel::Channel(int fd)
    :m_event(0),
    m_fd(fd),
    m_loop(nullptr)
{}

Channel::~Channel()
{
}

void Channel::processEvent()
{
    if (m_event & (EPOLLIN | EPOLLRDHUP | EPOLLPRI))
    {
        onRead();
    }
}

void Channel::addToLoop(EventLoop* loop)
{
    assert(m_loop == nullptr);
    assert(loop != nullptr);
    loop->addChannel(ChannelPtr(this));
    m_loop = loop;
}

void Channel::removeFromLoop()
{
    assert(m_loop != nullptr);
    m_loop->removeChannel(ChannelPtr(this));
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

