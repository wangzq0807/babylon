#pragma once
#include <vector>
#include "socket.h"

class EPoller
{
public:
    explicit EPoller(const SocketAddress& addr);
    ~EPoller();
    
    void addPoll(const SocketAddress& addr);

    int run(int interval);

protected:
    void updateEpollCtl(int nflags, SocketBase* socket);

private:
    int             m_epollfd;
    ServerSocket    m_serv;
    std::vector<Socket *>   m_clients;
};
