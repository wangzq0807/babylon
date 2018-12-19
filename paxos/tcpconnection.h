#include <functional>
#include <memory>
#include "channel.h"
class Socket;

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : public Channel
{
    typedef std::function<void(TcpConnectionPtr)> MessageCallback;
public:
    explicit TcpConnection(Socket* conn);
    virtual ~TcpConnection();

    void setMessageCallback(const MessageCallback& callback);

    void disconnect();
protected:
    virtual void onRead();
    //virtual void onWrite();
    //virtual void onClose();
    //virtual void onError();

private:
    Socket*             m_conn;
    MessageCallback     m_messageFunc;
};

