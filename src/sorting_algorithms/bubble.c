#include "sorts.h"
#include "../base.h"

void bubble_sort(i32 *arr, i32 length) {
    for (i32 i = 0; i < length-1; i++)
    {
        i32 swapped = 0;
        for (i32 j = 0; j < length-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                i32 tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

