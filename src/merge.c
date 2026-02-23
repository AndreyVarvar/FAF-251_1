#include "sorts.h"
#include <stdlib.h>


static void merge(int *arr, int *tmp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    for (int x = left; x <= right; x++)
    {
        tmp[x] = arr[x];
    }

    while (i <= mid && j <= right) {
        if (tmp[i] <= tmp[j]) {
            arr[k++] = tmp[i++];
        }
        else {
            arr[k++] = tmp[j++];
        }
    }

    while (i <= mid) {
        arr[k++] = tmp[i++];
    }
}

static void merge_sort_rec(int *arr, int *tmp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_rec(arr, tmp, left, mid);
        merge_sort_rec(arr, tmp, mid + 1, right);

        merge(arr, tmp, left, mid, right);
    }
}

void merge_sort(int *arr, int length)
{
    int *tmp = malloc(length * sizeof(int));
    merge_sort_rec(arr, tmp, 0, length - 1);
    free(tmp);
}