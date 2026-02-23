#include "sorts.h"

void insertion_sort(int *arr, int start, int end) {
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