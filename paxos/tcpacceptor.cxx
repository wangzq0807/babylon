#include "tcpacceptor.h"
#include <assert.h>

TcpAcceptor::TcpAcceptor(unsigned short port)
    :m_serv(),
    m_acceptFunc(nullptr),
    Channel()
{
    SocketAddress addr(port);
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);    
    setFd(m_serv.getSocketHandle());
}

TcpAcceptor::TcpAcceptor(const SocketAddress& addr)
    :m_serv(),
    m_acceptFunc(nullptr),
    Channel()
{
    m_serv.setNonBlocking(true);
    m_serv.listen(addr);    
    setFd(m_serv.getSocketHandle());
}

void TcpAcceptor::onRead()
{
    assert(m_acceptFunc != nullptr);
    Socket* sock = m_serv.accept();
    m_acceptFunc(sock);
}

void TcpAcceptor::setAcceptCallback(const AcceptCallback& func)
{
    m_acceptFunc = func;
}

