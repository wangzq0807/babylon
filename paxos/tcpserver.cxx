#include "tcpserver.h"
#include "eventloop.h"    
#include "tcpconnection.h"

TcpServer::TcpServer(EventLoop* loop,
                    unsigned short port)
    :m_loop(loop)
{
    m_acceptor = TcpAcceptorPtr(new TcpAcceptor(port));
    m_acceptor->addToLoop(loop);
    m_acceptor->setAcceptCallback(
        std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));
}

TcpServer::TcpServer(EventLoop* loop,
                    const SocketAddress& addr)
    :m_loop(loop)
{
    m_acceptor = TcpAcceptorPtr(new TcpAcceptor(addr));
    m_acceptor->addToLoop(loop);
    m_acceptor->setAcceptCallback(
        std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));
}

TcpServer::~TcpServer()
{
    for (auto itr : m_connections)
    {
        itr->removeFromLoop();
    }
    m_connections.clear();
}

void TcpServer::onNewConnection(Socket *sock)
{
    TcpConnectionPtr conn = TcpConnectionPtr(new TcpConnection(sock));
    conn->setMessageCallback(m_messageFunc);
    conn->addToLoop(m_loop);
    m_connections.push_back(conn); 
    if (m_connectFunc != nullptr)
        m_connectFunc(conn);
}

