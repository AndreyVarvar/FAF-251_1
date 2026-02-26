#include "sorts.h"
#include "../base.h"

static void heapify(i32 *arr, i32 length, i32 i)
{
    i32 max = i;
    i32 left = 2*i + 1;
    i32 right = 2*i + 2;

    if (left < length && arr[left] > arr[max])
    {
        max = left;
    }
    if (right < length && arr[right] > arr[max])
    {
        max = right;
    }
    if (max != i)
    {
        i32 tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, length, max);
    }
}

void heap_sort(i32 *arr, i32 length)
{
    for (i32 i = length/2; i >= 0; i--)
    {
        heapify(arr, length, i);
    }
    for (i32 i = length - 1; i > 0; i--)
    {
        i32 tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}
