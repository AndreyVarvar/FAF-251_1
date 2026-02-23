#include <stdio.h>
#include <stdlib.h>
#include "swap_list.h"

SwapNode *swap_list_init(i32 i, i32 j)
{
    SwapNode *node = calloc(1, sizeof(SwapNode));

    if (!node) return NULL;

    node->i = i;
    node->j = j;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

SwapNode *swap_list_push(SwapNode *node, i32 i, i32 j)
{
    node->next = calloc(1, sizeof(SwapNode));

    if (!node->next) return NULL;

    node->next->i = i;
    node->next->j = j;
    node->next->next = NULL;
    node->next->prev = node;

    return node->next;
}

void swap_list_destroy(SwapNode *root)
{
    SwapNode *current_node = root;
    SwapNode *next_node = root->next;

    while (next_node)
    {
        current_node = next_node;
        next_node = current_node->next;
        free(current_node->prev);
    }

    free(current_node);
}
