/*
 * event channel
 *
 * Copyright (c) 2023 hubugui <hubugui at gmail dot com> 
 * All rights reserved.
 *
 * This file is part of Eloop.
 */

#include <string.h>
#include <stdlib.h>

#include "event_channel.h"

struct event_channel {
    int fd;
    int mask;
    event_channel_proc procs[PROC_END_OF];
    void *userdata;

    struct buffer_pipe *pipe_recv;
    struct buffer_pipe *pipe_send;
};

static int 
_on_event(struct event_channel *channel, int event)
{
    if (channel->procs[event])  return channel->procs[event](channel);
    return -1;
}

struct event_channel *
event_channel_create(void)
{
    struct event_channel *channel = (struct event_channel *) calloc(1, sizeof(*channel));

    if (channel) {
        channel->pipe_recv = buffer_pipe_create();
        channel->pipe_send = buffer_pipe_create();
        if (!channel->pipe_recv || !channel->pipe_send)
            event_channel_delete(&channel);
    }    
    return channel;
}

void 
event_channel_delete(struct event_channel **channelp)
{
    struct event_channel *channel = channelp && (*channelp) ? (*channelp) : NULL;

    if (!channel)   return;
    if (channel->pipe_recv) buffer_pipe_delete(&channel->pipe_recv);
    if (channel->pipe_send) buffer_pipe_delete(&channel->pipe_send);
    free(channel);
    *channelp = NULL;
}

struct buffer_pipe *
event_channel_get_recv_pipe(struct event_channel *channel)
{
    return channel->pipe_recv;
}

struct buffer_pipe *
event_channel_get_send_pipe(struct event_channel *channel)
{
    return channel->pipe_send;
}

struct event_channel *
event_channel_clone(struct event_channel *channel)
{
    struct event_channel *ret = event_channel_create();

    if (ret)    memmove(ret, channel, sizeof(*channel));
    return ret;
}

void 
event_channel_copy(struct event_channel *dst, struct event_channel *src)
{
    memmove(dst, src, sizeof(*src));
}

void 
event_channel_set_fd(struct event_channel *channel, int fd)
{
    channel->fd = fd;
}

int 
event_channel_get_fd(struct event_channel *channel)
{
    return channel->fd;
}

void 
event_channel_set_userdata(struct event_channel *channel, void *userdata)
{
    channel->userdata = userdata;
}

void *
event_channel_get_userdata(struct event_channel *channel)
{
    return channel->userdata;
}

void 
event_channel_set_mask(struct event_channel *channel, int mask)
{
    channel->mask = mask;
}

int
event_channel_get_mask(struct event_channel *channel)
{
    return channel->mask;
}

void 
event_channel_add_mask(struct event_channel *channel, int mask)
{
    channel->mask |= mask;
}

void 
event_channel_remove_mask(struct event_channel *channel, int mask)
{
    channel->mask &= ~mask;
}

int 
event_channel_is_equal_mask(struct event_channel *channel, int mask)
{
    return channel->mask == mask;
}

int 
event_channel_is_exist_mask(struct event_channel *channel, int mask)
{
    return (channel->mask & mask) == mask ? 1 : 0;
}

void 
event_channel_clear_mask(struct event_channel *channel)
{
    channel->mask = FD_MASK_NONE;
}

void 
event_channel_set_read_proc(struct event_channel *channel, event_channel_proc proc)
{
    channel->procs[PROC_READ] = proc;
}

void 
event_channel_set_write_proc(struct event_channel *channel, event_channel_proc proc)
{
    channel->procs[PROC_WRITE] = proc;
}

void 
event_channel_set_error_proc(struct event_channel *channel, event_channel_proc proc)
{
    channel->procs[PROC_ERROR] = proc;
}

void 
event_channel_set_close_proc(struct event_channel *channel, event_channel_proc proc)
{
    channel->procs[PROC_CLOSE] = proc;
}

int 
event_channel_on_read(struct event_channel *channel)
{
    return _on_event(channel, PROC_READ);
}

int 
event_channel_on_write(struct event_channel *channel)
{
    return _on_event(channel, PROC_WRITE);
}

int 
event_channel_on_error(struct event_channel *channel)
{
    return _on_event(channel, PROC_ERROR);
}

int 
event_channel_on_close(struct event_channel *channel)
{
    return _on_event(channel, PROC_CLOSE);
}
