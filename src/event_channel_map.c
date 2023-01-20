/*
 * event channel map
 *
 * Copyright (c) 2023 hubugui <hubugui at gmail dot com> 
 * All rights reserved.
 *
 * This file is part of Eloop.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "event_channel_map.h"
#include "common/list.h"

struct event_channel_map {
    struct list *channel_list;
};

struct event_channel_map *
event_channel_map_create(void)
{
    struct event_channel_map *map = (struct event_channel_map *) calloc(1, sizeof(*map));

    if (map) {
        map->channel_list = list_create();
        if (!map->channel_list) event_channel_map_delete(&map);
    }    
    return map;
}

void 
event_channel_map_delete(struct event_channel_map **mapp)
{
    struct event_channel_map *map = mapp && (*mapp) ? (*mapp) : NULL;
    if (!map)   return;

    list_delete(&map->channel_list, NULL);
    free(map);
    *mapp = NULL;
}

static struct event_channel *
_map_find(struct event_channel_map *map, int fd, struct list_node **nodep)
{
    struct event_channel *channel;
	struct list_node *node;

    for (node = list_get_head(map->channel_list); node != NULL; node = list_get_next(node)) {
        if (nodep)  *nodep = node;

        channel = (struct event_channel *) list_get_data(node);
        if (event_channel_get_fd(channel) == fd)
            return channel;
    }

    return NULL;
}

int 
event_channel_map_add(struct event_channel_map *map, struct event_channel *channel)
{
    return list_append(map->channel_list, (void *) channel);
}

int 
event_channel_map_remove(struct event_channel_map *map, int fd)
{
    struct list_node *node = NULL;

    _map_find(map, fd, &node);
    return list_remove_node(map->channel_list, node, NULL);
}

struct event_channel *
event_channel_map_find(struct event_channel_map *map, int fd)
{
    return _map_find(map, fd, NULL);
}

size_t 
event_channel_map_get_length(struct event_channel_map *map)
{
    return list_length(map->channel_list);
}

int 
event_channel_map_get_max_fd(struct event_channel_map *map)
{
    int ret = -1;
    int fd;    
    struct event_channel *channel;
    struct list_node *node;

    for (node = list_get_head(map->channel_list); node != NULL; node = list_get_next(node)) {
        channel = (struct event_channel *) list_get_data(node);        
        fd = event_channel_get_fd(channel);
        if (fd > ret)   ret = fd;
    }

    return ret;
}

struct event_channel *
event_channel_map_get_head(struct event_channel_map *map, void **meta)
{
    struct event_channel *channel = NULL;
    struct list_node *node = list_get_head(map->channel_list);

    if (node) {
        channel = (struct event_channel *) list_get_data(node);
        if (meta)   *meta = node;
    }

    return channel;

}

struct event_channel *
event_channel_map_get_next(struct event_channel_map *map, void **meta)
{
    struct event_channel *channel = NULL;
    struct list_node *node = (struct list_node *) (*meta);

    if (node) {
        node = list_get_next(node);
        if (node) {
            channel = (struct event_channel *) list_get_data(node);
            if (meta)   *meta = node;
        }
    }

    return channel;
}
