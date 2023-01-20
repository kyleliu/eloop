#ifndef __EVENT_CHANNEL_MAP_H__
#define __EVENT_CHANNEL_MAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "event_channel.h"

struct event_channel_map;

struct event_channel_map *event_channel_map_create(void);
void event_channel_map_delete(struct event_channel_map **map);

int event_channel_map_add(struct event_channel_map *map, struct event_channel *channel);
int event_channel_map_remove(struct event_channel_map *map, int fd);

struct event_channel *event_channel_map_find(struct event_channel_map *map, int fd);
size_t event_channel_map_get_length(struct event_channel_map *map);
int event_channel_map_get_max_fd(struct event_channel_map *map);

struct event_channel *event_channel_map_get_head(struct event_channel_map *map, void **meta);
struct event_channel *event_channel_map_get_next(struct event_channel_map *map, void **meta);

#ifdef __cplusplus
}
#endif
#endif
