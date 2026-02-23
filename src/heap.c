#include "sorts.h"


static void heapify(int *arr, int length, int i)
{
    int max = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
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
        int tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, length, max);
    }
}

void heap_sort(int *arr, int length)
{
    for (int i = length/2; i >= 0; i--)
    {
        heapify(arr, length, i);
    }
    for (int i = length - 1; i > 0; i--)
    {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}