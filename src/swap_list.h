#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "base.h"

typedef struct SwapNode {
    i32 i;
    i32 j;
    struct SwapNode *next;
    struct SwapNode *prev;
} SwapNode;

SwapNode *swap_list_init(i32 i, i32 j);
SwapNode *swap_list_push(SwapNode *node, i32 i, i32 j);
void swap_list_destroy(SwapNode *root);

#endif
