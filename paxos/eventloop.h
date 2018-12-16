#pragma once
#include <boost/utility.hpp>
#include <memory>
#include "epoller.h"

class Channel;
typedef std::shared_ptr<Channel> ChannelPtr;

class EventLoop : public boost::noncopyable
{
public:
    EventLoop();
    void run();

    void updateChannel(const ChannelPtr& channel);
    void removeChannel(const ChannelPtr& channel);
private:
    EPoller     m_poll;
};
