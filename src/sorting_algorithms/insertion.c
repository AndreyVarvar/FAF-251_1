#include "sorts.h"
#include "../base.h"

void insertion_sort(i32 *arr, i32 length) {
    i32 start = 0;
    i32 end = length - 1;
    for (i32 i = start + 1 ; i <= end; i++) 
    {
        i32 key = arr[i];
        i32 j = i - 1 ;
        while (j >= start && arr[j] > key) 
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}
