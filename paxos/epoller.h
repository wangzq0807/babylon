#pragma once
#include <vector>
#include <memory>
#include "socket.h"

class Channel;

class EPoller
{
    typedef std::shared_ptr<Channel> ChannelPtr;
public:
    explicit EPoller();
    ~EPoller();
    
    int run(int interval);

    void addChannel(const ChannelPtr& channel);
    void removeChannel(const ChannelPtr& channel);

protected:
    void updateEpollCtl(int nflags, const ChannelPtr& channel);

private:
    int             m_epollfd;
};
