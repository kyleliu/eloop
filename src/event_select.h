#ifndef __EVENT_SELECT_H__
#define __EVENT_SELECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "event_channel.h"
#include "event_channel_map.h"

struct event_io;

struct event_io *event_io_select_create(void);
void event_io_select_delete(struct event_io **eiop);
int event_io_select_add_fd(struct event_io *eio, struct event_channel *channel);
int event_io_select_remove_fd(struct event_io *eio, struct event_channel *channel);
int event_io_select_poll(struct event_io *eio, struct event_channel_map *ec_map, unsigned long long timeout);

#ifdef __cplusplus
}
#endif
#endif
