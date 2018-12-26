#include "tcpconnection.h"
#include "socket.h"

TcpConnection::TcpConnection(Socket *conn)
    :m_conn(conn),
    Channel()
{
    setFd(conn->getSocketHandle());
}

TcpConnection::~TcpConnection()
{
    delete m_conn;
}
void TcpConnection::setMessageCallback(const MessageCallback& callback)
{
    m_messageFunc = callback;
}

void TcpConnection::onRead()
{
    char buf[1024];
    m_conn->receive(buf, 1024);
    m_messageFunc(TcpConnectionPtr(this));
}

void TcpConnection::disconnect()
{
    removeFromLoop();
    m_conn->close();
}

