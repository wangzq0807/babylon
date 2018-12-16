#pragma once
#include <boost/utility.hpp>
#include <memory>

class EventLoop;

class Channel : public boost::noncopyable,
                public std::enable_shared_from_this<Channel>
{
public:
    Channel(int fd);
    virtual ~Channel();

    void add(EventLoop* loop);
    void remove();

    void setEvent(int event);
    virtual void processEvent();

protected:
    virtual void onRead();
    virtual void onWrite();
    virtual void onClose();
    virtual void onError();

private:
    int         m_event;
    int         m_fd;
    EventLoop*  m_loop;
};

