/*
 * list
 *
 * Copyright (c) 2023 hubugui <hubugui at gmail dot com> 
 * All rights reserved.
 *
 * This file is part of Eloop.
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list_node {
    struct list_node *prev, *next;
    void *data;
};

struct list {
    struct list_node *head, *tail;
    size_t length;
};

static struct list_node *
_data_2_node(void *data)
{
    struct list_node *node = calloc(1, sizeof(struct list_node));
    if (node)   node->data = data;
    return node;
}

struct list * 
list_create(void)
{
    return calloc(1, sizeof(struct list));
}

void 
list_delete(struct list **listp, list_free_data free_data)
{
    struct list *list = listp && (*listp) ? (*listp) : NULL;
    if (!list)  return;

    while (list_remove_node(list, list_get_head(list), free_data) == 1)
        ;

    free(list);
    *listp = NULL;
}

size_t 
list_length(struct list *list)
{
    return list->length; 
}

void *
list_get_data(struct list_node *node)
{
    return node->data;
}

struct list_node *
list_get_head(struct list *list)
{
    return list->head;
}

struct list_node *
list_get_tail(struct list *list)
{
    return list->tail;
}

struct list_node *
list_get_next(struct list_node *node)
{
    return node->next;
}

struct list_node *
list_get_prev(struct list_node *node)
{
    return node->prev;
}

int 
list_append(struct list *list, void *data)
{
    return list_append_after(list, data, list->tail);
}

int 
list_append_before(struct list *list, void *data, struct list_node *pos)
{
    struct list_node *node = _data_2_node(data);

    if (node) {
        /* pos prev */
        if (pos && pos->prev)   pos->prev->next = node;
        /* node */
        node->prev = pos ? pos->prev : NULL;
        node->next = pos;
        /* pos */
        if (pos)                pos->prev = node;
        /* head */
        if (list->head == pos)  list->head = node;
        /* tail */
        if (list->tail == NULL)  list->tail = node;

        list->length++;
    }
    return node ? 0 : -1;
}

int 
list_append_after(struct list *list, void *data, struct list_node *pos)
{
    struct list_node *node = _data_2_node(data);

    if (node) {
        /* pos next */
        if (pos && pos->next)   pos->next->prev = node;
        /* node */
        node->prev = pos;
        node->next = pos ? pos->next : NULL;
        /* pos */
        if (pos)                pos->next = node;
        /* head */
        if (list->head == NULL)  list->head = node;
        /* tail */
        if (list->tail == pos)  list->tail = node;

        list->length++;
    }
    return node ? 0 : -1;
}

struct list_node *
list_find(struct list *list, void *data, list_data_cmp cmp)
{
    return list_find_begin(list, list_get_head(list), data, cmp);
}

struct list_node *
list_find_begin(struct list *list, struct list_node *begin, void *data, list_data_cmp cmp)
{
    int is_equal;
    struct list_node *ret = NULL, *node;

    for (node = begin; node != NULL; node = list_get_next(node)) {
        void *ndata = list_get_data(node);

        if (cmp)    is_equal = cmp(ndata, data) == 0;
        else        is_equal = ndata == data;

        if (is_equal) {
            ret = node;
            break;
        }        
    }

    return ret;
}

int 
list_is_exist(struct list *list, void *data, list_data_cmp cmp)
{
    struct list_node *node = list_find(list, data, cmp);
    return node ? 1 : 0;
}

int 
list_remove(struct list *list, void *data, list_data_cmp cmp, list_free_data free_data)
{
    return list_remove_node(list, list_find(list, data, cmp), free_data);
}

unsigned int 
list_remove_data(struct list *list, void *data, list_data_cmp cmp, list_free_data free_data)
{
    unsigned int ret = 0;
    struct list_node *node;
    struct list_node *begin = list_get_head(list);

    while (begin != NULL) {
        node = list_find_begin(list, begin, data, cmp);

        if (node) {
            begin = list_get_next(node);
            list_remove_node(list, node, free_data);
            ret++;
        } else
            begin = NULL;
    }

    return ret;
}

int 
list_remove_node(struct list *list, struct list_node *node, list_free_data free_data)
{
    int ret = 1;
    struct list_node *prev, *next;

    if (list == NULL || node == NULL)
        return 0;

    prev = list_get_prev(node);
    next = list_get_next(node);

    if (prev)   prev->next = next;
    if (next)   next->prev = prev;

    if (list->head == node) list->head = next;
    if (list->tail == node) list->tail = prev;
    if (list->length > 0)   list->length--;

    if (free_data)  free_data(list_get_data(node));
    free(node);
    return ret;
}

unsigned int 
list_remove_all(struct list *list, list_free_data free_data)
{
    unsigned int ret = 0;
    struct list_node *node;

    for (node = list_get_head(list); node != NULL; node = list_get_head(list)) {
        list_remove_node(list, node, free_data);
        ret++;
    }    

    return ret;    
}
