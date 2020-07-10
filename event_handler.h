#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

typedef int Handle;
class EventHandler {
public:
    EventHandler() {}
    virtual ~EventHandler() {}
    virtual Handle getHandle() const = 0;
    virtual void handleRead() = 0;
    virtual void handleWrite() = 0;
    virtual void handleError() = 0;
};

#endif // EVENTHANDLER_H
