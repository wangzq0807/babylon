#pragma once
#include "channel.h"

class TcpAcceptor : public Channel
{
public:
    TcpAcceptor(const SocketAddress& addr);
private:
    ServerSocket    m_serv;
};

