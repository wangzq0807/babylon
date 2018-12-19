#include "tcpacceptor.h"

TcpAcceptor::TcpAcceptor(unsigned short port)
    :m_serv(),
    Channel(m_serv.getSocketHandle())
{
    SocketAddress addr(port);
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);    
}

TcpAcceptor::TcpAcceptor(const SocketAddress& addr)
    :m_serv(),
    Channel(m_serv.getSocketHandle())
{
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);    
}

void TcpAcceptor::onRead()
{
    Socket* sock = m_serv.accept();
    m_acceptFunc(sock);
}

void TcpAcceptor::setAcceptCallback(const AcceptCallback& func)
{
    m_acceptFunc = func;
}

