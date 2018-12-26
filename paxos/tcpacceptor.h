#pragma once
#include <functional>
#include "socket.h"
#include "channel.h"

class TcpAcceptor : public Channel
{
    typedef std::function<void(Socket*)> AcceptCallback;
public:
    TcpAcceptor(unsigned short port);
    TcpAcceptor(const SocketAddress& addr);

    void setAcceptCallback(const AcceptCallback& func);
protected:
    virtual void onRead();
    //virtual void onWrite();
    //virtual void onClose();
    //virtual void onError();
private:
    ServerSocket    m_serv;
    AcceptCallback  m_acceptFunc;
};

typedef std::shared_ptr<TcpAcceptor>    TcpAcceptorPtr;

