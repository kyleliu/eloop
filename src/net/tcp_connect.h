#ifndef __TCP_CONNECT_H__
#define __TCP_CONNECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../event_loop.h"
#include "../event_channel.h"

struct tcp_connect;

typedef int (*tcp_connect_proc)(struct tcp_connect *connect);

struct tcp_connect *tcp_connect_create(int fd, 
                                            struct event_loop *e_loop, 
                                            tcp_connect_proc read_proc, 
                                            tcp_connect_proc write_proc, 
                                            tcp_connect_proc close_proc);
void tcp_connect_delete(struct tcp_connect **connectp);

int tcp_connect_write(struct tcp_connect *connect);

int tcp_connect_mark_read(struct tcp_connect *connect);

int tcp_connect_mark_write(struct tcp_connect *connect);
int tcp_connect_unmark_write(struct tcp_connect *connect);

struct event_loop *tcp_connect_get_event_loop(struct tcp_connect *connect);
struct event_channel *tcp_connect_get_event_channel(struct tcp_connect *connect);

void tcp_connect_set_userdata(struct tcp_connect *connect, void *userdata);
void *tcp_connect_get_userdata(struct tcp_connect *connect);

#ifdef __cplusplus
}
#endif
#endif
