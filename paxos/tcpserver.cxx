#include "tcpserver.h"

TcpServer::TcpServer(addr)
{
    m_loop->addPoll(addr);
}

void TcpServer::onNewConnection(Socket *sock)
{
    TcpConnectionPtr conn = new TcpConnection(sock);
    m_loop.add(conn);
    m_Connections.push_back(conn); 
}

