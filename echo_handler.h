#ifndef ECHOHANDLER_H
#define ECHOHANDLER_H

#include <QString>
#include "event_handler.h"

class EchoHandler : public EventHandler
{
public:
    EchoHandler(QString ip,int port);
    ~EchoHandler();
    Handle getHandle() const;

    void handleRead();
    void handleWrite();
    void handleError();

private:
    Handle m_echo_fd;
    char* m_buf;
    static const int MAX_SIZE = 1024;
};

#endif // ECHOHANDLER_H
