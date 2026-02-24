#include "sorts.h"

void selection_sort(int *arr, int length) {
    int i, j, min_idx, temp;
    for (i = 0; i < length - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < length; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
