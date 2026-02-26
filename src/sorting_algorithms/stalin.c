#include <stdlib.h>

#include "sorts.h"
#include "../base.h"

static void move_to_front(i32 *a, i32 src, i32 dst)
{
    i32 temp = a[src];
    for(i32 i = src; i > dst; --i)
        a[i] = a[i - 1];
    a[dst] = temp;
}

void kind_stalin_sort(i32 *a, i32 length)
{
    i32 j = 0;
    while(1)
    {
        i32 moved = 0;

        for(i32 i = 0; i < length - 1 - j; ++i)
        {
            if(a[i] > a[i + 1])
            {
                move_to_front(a, i + 1, moved);
                ++moved;
            }
        }

        ++j;
        if(moved == 0)
            break;
    }
}

i32 *cruel_stalin_sort(i32 *arr, i32 *length)
{
    i32 new_length = 1;
    i32 current_element = arr[0];
    for (i32 i = 1; i < *length; ++i)
        if (arr[i] >= current_element)
        {
            current_element = arr[i];
            new_length++;
        }

    i32 *new_arr = malloc(new_length * sizeof *new_arr);

    current_element = arr[0];
    new_arr[0] = current_element;

    i32 stalin_index = 1;
    for (i32 i = 1; i < *length; ++i)
        if (arr[i] >= current_element)
        {
            new_arr[stalin_index] = arr[i];
            current_element = arr[i];
            stalin_index++;
        }

    free(arr);
    *length = new_length;
    return new_arr;
}
