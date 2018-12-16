#include "channel.h"
#include <sys/epoll.h>

Channel::Channel(int fd)
    :m_event(0),
    m_fd(fd),
    m_loop(nullptr)
{}

Channel::~Channel()
{}

void Channel::processEvent()
{
    if (m_event & (EPOLLIN | EPOLLRDHUP | EPOLLPRI))
    {
        onRead();
    }
}
void Channel::add(EventLoop* loop)
{

}

void Channel::remove()
{

}

void Channel::onRead()
{}
void Channel::onWrite()
{}
void Channel::onClose()
{}
void Channel::onError()
{}

