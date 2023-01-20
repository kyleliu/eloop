#ifndef __EVENT_CHANNEL_H__
#define __EVENT_CHANNEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "buffer_pipe.h"
#include "event.h"

struct event_channel;

enum {
    PROC_READ = 0,
    PROC_WRITE,
    PROC_ERROR,
    PROC_CLOSE,
    PROC_END_OF,    
};

typedef int (*event_channel_proc)(struct event_channel *channel);

struct event_channel *event_channel_create(void);
void event_channel_delete(struct event_channel **channel);

struct buffer_pipe *event_channel_get_recv_pipe(struct event_channel *channel);
struct buffer_pipe *event_channel_get_send_pipe(struct event_channel *channel);

struct event_channel *event_channel_clone(struct event_channel *channel);
void event_channel_copy(struct event_channel *dst, struct event_channel *src);

void event_channel_set_fd(struct event_channel *channel, int fd);
int event_channel_get_fd(struct event_channel *channel);

void event_channel_set_userdata(struct event_channel *channel, void *userdata);
void *event_channel_get_userdata(struct event_channel *channel);

void event_channel_set_mask(struct event_channel *channel, int mask);
int event_channel_get_mask(struct event_channel *channel);

void event_channel_add_mask(struct event_channel *channel, int mask);
void event_channel_remove_mask(struct event_channel *channel, int mask);
int event_channel_is_equal_mask(struct event_channel *channel, int mask);
int event_channel_is_exist_mask(struct event_channel *channel, int mask);
void event_channel_clear_mask(struct event_channel *channel);

void event_channel_set_read_proc(struct event_channel *channel, event_channel_proc proc);
void event_channel_set_write_proc(struct event_channel *channel, event_channel_proc proc);
void event_channel_set_error_proc(struct event_channel *channel, event_channel_proc proc);
void event_channel_set_close_proc(struct event_channel *channel, event_channel_proc proc);

int event_channel_on_read(struct event_channel *channel);
int event_channel_on_write(struct event_channel *channel);
int event_channel_on_error(struct event_channel *channel);
int event_channel_on_close(struct event_channel *channel);

#ifdef __cplusplus
}
#endif
#endif
