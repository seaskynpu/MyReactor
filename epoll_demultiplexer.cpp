
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <sys/epoll.h>
#include <QVector>
#include "epoll_demultiplexer.h"



EpollDemultiplexer::EpollDemultiplexer()
{
    m_epoll_fd = epoll_create(FD_SETSIZE);
    assert(m_epoll_fd != -1);
    m_fd_num = 0;
}

EpollDemultiplexer::~EpollDemultiplexer()
{
    close(m_epoll_fd);
}

int EpollDemultiplexer::regist(Handle handle, Event evt)
{
    struct epoll_event ev;
    ev.data.fd = handle;
    if (evt & ReadEvent)
    {
        ev.events |= EPOLLIN;
    }
    if (evt & WriteEvent)
    {
        ev.events |= EPOLLOUT;
    }
    ev.events |= EPOLLET;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handle, &ev) != 0)
    {
        if (errno == ENOENT) {
            if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handle, &ev) != 0)
            {
                std::cerr << "epoll_ctl add error " << errno << std::endl;
                return -errno;
            }
        }
    }
    ++m_fd_num;
    return 0;
}

int EpollDemultiplexer::remove(Handle handle)
{
    struct epoll_event ev;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handle, &ev) != 0) {
        std::cerr << "epoll_ctl del error" << errno << std::endl;
        return -errno;
    }
    --m_fd_num;
    return 0;
}

int EpollDemultiplexer::WaitEvents(QMap<Handle, EventHandler*>& handlers, int timeout)
{
    QVector<struct epoll_event> events(m_fd_num);
    int num = epoll_wait(m_epoll_fd, &events[0], m_fd_num, timeout);
    if (num < 0)
    {
        std::cerr << "WARNING: epoll_wait error " << errno << std::endl;
        return num;
    }

    for (int i = 0; i < num; ++i)
    {
        Handle handle = events[i].data.fd;
        if ((EPOLLHUP|EPOLLERR) & events[i].events)
        {
            assert(handlers[handle] != NULL);
            (handlers[handle])->handleError();
        }
        else
        {
            if ((EPOLLIN) & events[i].events)
            {
                assert(handlers[handle] != NULL);
                (handlers[handle])->handleRead();
            }
            if (EPOLLOUT & events[i].events)
            {
                (handlers[handle])->handleWrite();
            }
        }
    }
    return num;
}




