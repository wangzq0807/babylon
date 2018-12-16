#include "tcpacceptor.h"

TcpAcceptor::TcpAcceptor(const SocketAddress& addr)
{
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);    
}

