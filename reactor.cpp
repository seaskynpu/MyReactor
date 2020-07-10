#include "reactor.h"
#include <assert.h>
#include <new>

Reactor Reactor::reactor;

Reactor& Reactor::getInstance() {
    return reactor;
}

Reactor::Reactor() {
    m_demultiplexer = new (std::nothrow)EpollDemultiplexer();
    assert(m_demultiplexer != NULL);
}

Reactor::~Reactor()
{
    QMap<Handle, EventHandler*>::iterator iter = m_handlers.begin();
    for(; iter != m_handlers.end(); ++iter)
    {
        delete iter.value();
    }

    if (m_demultiplexer != NULL) {
        delete m_demultiplexer;
        m_demultiplexer = NULL;
    }
}


int Reactor::regist(EventHandler* handler, Event evt)
{
    int handle = handler->getHandle();
    if (m_handlers.find(handle) == m_handlers.end())
    {
        m_handlers.insert(handle, handler);
    }
    return m_demultiplexer->regist(handle, evt);

}


int Reactor::dispatch(int timeout) {
    return m_demultiplexer->WaitEvents(m_handlers, timeout);
}

