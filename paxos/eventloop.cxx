#include "eventloop.h"

EventLoop::EventLoop()
{

}

void EventLoop::addChannel(const ChannelPtr& channel)
{
    m_poll.addChannel(channel);
}

void EventLoop::removeChannel(const ChannelPtr& channel)
{
    m_poll.removeChannel(channel);
}

void EventLoop::run()
{
    while(true)
    {
    }
}

