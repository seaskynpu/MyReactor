#include <QCoreApplication>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include "reactor.h"
#include "echo_handler.h"
#include "event.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Reactor& actor=Reactor::getInstance();
    EventHandler* echoHandler= new EchoHandler(QString("192.168.3.15"),54432);
    actor.regist(echoHandler, ReadEvent);
    actor.dispatch(-1);

    return a.exec();
}

