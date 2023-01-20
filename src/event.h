#ifndef __EVENT_H__
#define __EVENT_H__

enum fd_mask {
    FD_MASK_NONE = 0,
    FD_MASK_READ = 1,
    FD_MASK_WRITE = 2,
    FD_MASK_ERROR = 4,
    FD_MASK_CLOSE = 8,
};

struct event_io_event {
    int fd;
    enum fd_mask mask;
};

#endif
