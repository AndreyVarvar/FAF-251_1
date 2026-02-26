#include <stdlib.h>

#include "sorts.h"
#include "../base.h"

static void merge(i32 *arr, i32 *tmp, i32 left, i32 mid, i32 right) {
    i32 i = left;
    i32 j = mid + 1;
    i32 k = left;

    for (i32 x = left; x <= right; x++)
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

static void merge_sort_rec(i32 *arr, i32 *tmp, i32 left, i32 right) {
    if (left < right) {
        i32 mid = left + (right - left) / 2;

        merge_sort_rec(arr, tmp, left, mid);
        merge_sort_rec(arr, tmp, mid + 1, right);

        merge(arr, tmp, left, mid, right);
    }
}

void merge_sort(i32 *arr, i32 length)
{
    i32 *tmp = malloc(length * sizeof(i32));
    merge_sort_rec(arr, tmp, 0, length - 1);
    free(tmp);
}
