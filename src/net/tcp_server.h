#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

struct tcp_server;

struct tcp_server *tcp_server_open(const char *addr, unsigned short port, int backlog, char *err, size_t err_length);
void tcp_server_close(struct tcp_server **serverp);

int tcp_server_get_fd(struct tcp_server *server);

#ifdef __cplusplus
}
#endif
#endif
