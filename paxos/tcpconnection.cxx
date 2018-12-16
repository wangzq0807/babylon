#include "tcpconnection.h"
#include "socket.h"

TcpConnection::TcpConnection(Socket *conn)
    :m_conn(conn),
    Channel(conn->getSocketHandle())
{}

TcpConnection::~TcpConnection()
{
    delete m_conn;
}

void TcpConnection::onRead()
{
    m_messageCallback(TcpConnectionPtr(this));
}

