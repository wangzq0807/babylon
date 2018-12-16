#pragma once
#include <boost/noncopyable.hpp>
#include <algorithm>
#include "socket.h"

class EventLoop;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void(TcpConnectionPtr)> MessageCallback;

class TcpServer : public boost::noncopyable
{
public:
    TcpServer(const EventLoop* loop,
              unsigned short port);
    TcpServer(const EventLoop* loop,
              const SocketAddress& addr);

    void setConnectCallback() {

    }

    void setMessageCallback(const MessageCallback& func) {
        m_messageCallback = func;
    }
protected:
    void onNewConnection(Socket *sock);
private
    EventLoop*                      m_loop;
    std::vector<TcpConnectionPtr>   m_Connections;
};


