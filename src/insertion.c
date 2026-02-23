#include "sorts.h"

void insertion_sort(int *arr, int length) {
    int start = 0;
    int end = length - 1;
    for (int i = start + 1 ; i <= end; i++) 
    {
        int key = arr[i];
        int j = i - 1 ;
        while (j >= start && arr[j] > key) 
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}