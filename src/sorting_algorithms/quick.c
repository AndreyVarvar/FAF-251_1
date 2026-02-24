#include "sorts.h"
#include "../utils.h"
#include "../base.h"

static int median_of_three_index(int *a, int low, int mid, int high)
{
    if ((a[low] <= a[mid] && a[mid] <= a[high]) || (a[high] <= a[mid] && a[mid] <= a[low]))
        return mid;
    if ((a[mid] <= a[low] && a[low] <= a[high]) || (a[high] <= a[low] && a[low] <= a[mid]))
        return low;
    return high;
}

static int partition(int *a, int low, int high)
{
    int mid = low + (high - low) / 2;
    int pivot_index = median_of_three_index(a, low, mid, high);
    int pivot = a[pivot_index];

    SWAP(i32, &a[low], &a[pivot_index]);

    int i = low - 1;
    int j = high + 1;

    while (1)
    {
        do { i++; } while (a[i] < pivot);
        do { j--; } while (a[j] > pivot);

        if (i >= j)
            return j;

        SWAP(i32, &a[i], &a[j]);
    }
}

static void quick_sort_rec(int *a, int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);
        quick_sort_rec(a, low, p);
        quick_sort_rec(a, p + 1, high);
    }
}

void quick_sort(int *arr, int length)
{
    quick_sort_rec(arr, 0, length - 1);
}
