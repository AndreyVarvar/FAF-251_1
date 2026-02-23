#include "sorts.h"
#include <stdlib.h>


static void move_to_front(int *a, int src, int dst)
{
    int temp = a[src];
    for(int i = src; i > dst; --i)
        a[i] = a[i - 1];
    a[dst] = temp;
}

void kind_stalin_sort(int *a, int length)
{
    int j = 0;
    while(1)
    {
        int moved = 0;

        for(int i = 0; i < length - 1 - j; ++i)
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

int *cruel_stalin_sort(int *arr, int *length)
{
    int new_length = 1;
    int current_element = arr[0];
    for (int i = 1; i < *length; ++i)
        if (arr[i] >= current_element)
        {
            current_element = arr[i];
            new_length++;
        }

    int *new_arr = malloc(new_length * sizeof *new_arr);

    current_element = arr[0];
    new_arr[0] = current_element;

    int stalin_index = 1;
    for (int i = 1; i < *length; ++i)
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