#ifndef EVENTDEMULTIPLEXER_H
#define EVENTDEMULTIPLEXER_H


#include <QMap>
#include "event_handler.h"
#include "event.h"

class EventDemultiplexer {
public:
    EventDemultiplexer() {}
    virtual ~EventDemultiplexer()  {}

    virtual int regist(Handle handle, Event evt) = 0;
    virtual int remove(Handle handle) = 0;
    virtual int WaitEvents(QMap<Handle, EventHandler*>& handlers, int timeout = 0) = 0;
};

#endif // EVENTDEMULTIPLEXER_H
