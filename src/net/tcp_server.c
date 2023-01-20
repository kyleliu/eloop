/*
 * tcp server
 *
 * Copyright (c) 2023 hubugui <hubugui at gmail dot com> 
 * All rights reserved.
 *
 * This file is part of Eloop.
 */

#include <string.h>
#include <stdlib.h>

#include "tcp_server.h"
#include "net.h"

struct tcp_server {
    int fd;
};

struct tcp_server *
tcp_server_open(const char *addr, unsigned short port, int backlog, char *err, size_t err_length)
{
    struct tcp_server *server = (struct tcp_server *) calloc(1, sizeof(*server));

    if (server) {
        server->fd = net_tcp_server(addr, port, backlog, err, err_length);
        if (server->fd == -1) {
            free(server);
            server = NULL;
        }
    }

    return server;
}

void 
tcp_server_close(struct tcp_server **serverp)
{
    if (serverp && *serverp) {
        net_fd_close((*serverp)->fd);
        free(*serverp);
        *serverp = NULL;
    }
}

int 
tcp_server_get_fd(struct tcp_server *server)
{
    return server->fd;
}
