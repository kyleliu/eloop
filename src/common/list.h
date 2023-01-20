#ifndef __LIST__
#define __LIST__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * non-thread safe
 */

struct list;
struct list_node;

typedef void (*list_free_data)(void *);
typedef int (*list_data_cmp)(void *, void *);

struct list *list_create(void);
void list_delete(struct list **listp, list_free_data free_data);

size_t list_length(struct list *list);

void *list_get_data(struct list_node *node);
struct list_node *list_get_head(struct list *list);
struct list_node *list_get_tail(struct list *list);
struct list_node *list_get_next(struct list_node *node);
struct list_node *list_get_prev(struct list_node *node);

struct list_node *list_find(struct list *list, void *data, list_data_cmp cmp);
struct list_node *list_find_begin(struct list *list, struct list_node *begin, void *data, list_data_cmp cmp);
int list_is_exist(struct list *list, void *data, list_data_cmp cmp);

int list_append(struct list *list, void *data);
int list_append_before(struct list *list, void *data, struct list_node *pos);
int list_append_after(struct list *list, void *data, struct list_node *pos);

int list_remove(struct list *list, void *data, list_data_cmp cmp, list_free_data free_data);

unsigned int list_remove_data(struct list *list, void *data, list_data_cmp cmp, list_free_data free_data);
int list_remove_node(struct list *list, struct list_node *node, list_free_data free_data);

unsigned int list_remove_all(struct list *list, list_free_data free_data);

#ifdef __cplusplus
}
#endif
#endif
