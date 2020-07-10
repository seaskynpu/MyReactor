#ifndef EVENT_H
#define EVENT_H
typedef unsigned int Event;
enum EventMask {
    ReadEvent  = 0x01,
    WriteEvent = 0x02,
    ErrorEvent = 0x04,
    EventMask  = 0xff
};
#endif // EVENT_H
