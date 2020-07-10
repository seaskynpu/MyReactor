#ifndef REACTOR_H
#define REACTOR_H

#include "epoll_demultiplexer.h"
#include "event_handler.h"
#include "event.h"


class Reactor {
public:

    int regist(EventHandler* handler, Event evt);
    int remove(EventHandler* handler);
    int dispatch(int timeout = 0);
    static Reactor& getInstance();

private:
    Reactor();
    ~Reactor();

private:

    static Reactor reactor;
    EventDemultiplexer * m_demultiplexer;
    QMap<Handle, EventHandler*> m_handlers;
};

#endif // REACTOR_H
