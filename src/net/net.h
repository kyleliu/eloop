#ifndef __Eloop_NET_H__
#define __Eloop_NET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#if defined(__linux) || defined(__linux__) 
#endif

int net_init();
void net_finalize();

int net_tcp_connect(const char *addr, unsigned short port, char *err, size_t err_length);
int net_fd_close(int *fd);
int net_fd_shutdown_read(int fd);
int net_fd_shutdown_write(int fd);

int net_tcp_set_reuse(int fd);
int net_tcp_set_delay(int fd);
int net_tcp_set_nodelay(int fd);

int net_tcp_server(const char *addr, unsigned short port, int backlog, char *err, size_t err_length);
int net_tcp_accept(int fd, char *ip, size_t ip_length, unsigned short *port, char *err, size_t err_length);

int net_fd_set_block_direct(int fd, char is_block, int *error);
int net_fd_set_block(int fd, int *error);
int net_fd_set_noblock(int fd, int *error);

int net_fd_read(int fd, char *buffer, size_t length, int *error);
int net_fd_write(int fd, char *buffer, size_t length);

int net_get_last_error();

#ifdef __cplusplus
}
#endif
#endif
