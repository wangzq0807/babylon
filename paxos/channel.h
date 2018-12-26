#pragma once
#include <boost/utility.hpp>
#include <memory>

class EventLoop;

class Channel : public boost::noncopyable,
                public std::enable_shared_from_this<Channel>
{
public:
    Channel();
    virtual ~Channel();

    void addToLoop(EventLoop* loop);
    void removeFromLoop();

    void setFd(int fd) {
        m_fd = fd;
    }
    int getFd() {
        return m_fd;
    }

    virtual void processEvent(unsigned int events);

protected:
    virtual void onRead();
    virtual void onWrite();
    virtual void onClose();
    virtual void onError();

private:
    unsigned int    m_events;
    int             m_fd;
    EventLoop*      m_loop;
};

typedef std::shared_ptr<Channel> ChannelPtr;

