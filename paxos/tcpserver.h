#pragma once
#include <boost/noncopyable.hpp>
#include <algorithm>
#include <memory>
#include <functional>
#include <vector>
#include "socket.h"
#include "tcpacceptor.h"

class EventLoop;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void(TcpConnectionPtr)> MessageCallback;

class TcpServer : public boost::noncopyable
{
public:
    TcpServer(EventLoop* loop,
              unsigned short port);
    TcpServer(EventLoop* loop,
              const SocketAddress& addr);
    virtual ~TcpServer();

    void setConnectCallback(const MessageCallback& func) {
        m_connectFunc = func;
    }

    void setMessageCallback(const MessageCallback& func) {
        m_messageFunc = func;
    }
protected:
    void onNewConnection(Socket *sock);

private:
    EventLoop                       *m_loop;
    TcpAcceptorPtr                  m_acceptor;
    MessageCallback                 m_connectFunc;
    MessageCallback                 m_messageFunc;
    std::vector<TcpConnectionPtr>   m_connections;
};


