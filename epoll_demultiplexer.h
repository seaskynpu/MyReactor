#ifndef EPOLLDEMULTIPLEXER_H
#define EPOLLDEMULTIPLEXER_H


#include <QSet>
#include <QMap>

#include "event_handler.h"
#include "event_demultiplexer.h"


class EpollDemultiplexer : public EventDemultiplexer
{
public:
    EpollDemultiplexer();
    ~EpollDemultiplexer();

    virtual int regist(Handle handle, Event evt);
    virtual int remove(Handle handle);
    virtual int WaitEvents(QMap<Handle, EventHandler*> & handlers, int timeout = 0);

private:

    int  m_epoll_fd;
    int  m_fd_num;
};

#endif // EPOLLDEMULTIPLEXER_H
