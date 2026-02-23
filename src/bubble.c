#include "sorts.h"

void bubble_sort(int *arr, int length) {
    for (int i = 0; i < length-1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < length-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int tmp = arr[j];
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