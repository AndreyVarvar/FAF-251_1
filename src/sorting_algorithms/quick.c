#include "sorts.h"
#include "../utils.h"
#include "../base.h"

static i32 median_of_three_index(i32 *a, i32 low, i32 mid, i32 high)
{
    if ((a[low] <= a[mid] && a[mid] <= a[high]) || (a[high] <= a[mid] && a[mid] <= a[low]))
        return mid;
    if ((a[mid] <= a[low] && a[low] <= a[high]) || (a[high] <= a[low] && a[low] <= a[mid]))
        return low;
    return high;
}

static i32 partition(i32 *a, i32 low, i32 high)
{
    i32 mid = low + (high - low) / 2;
    i32 pivot_index = median_of_three_index(a, low, mid, high);
    i32 pivot = a[pivot_index];

    SWAP(i32, &a[low], &a[pivot_index]);

    i32 i = low - 1;
    i32 j = high + 1;

    while (1)
    {
        do { i++; } while (a[i] < pivot);
        do { j--; } while (a[j] > pivot);

        if (i >= j)
            return j;

        SWAP(i32, &a[i], &a[j]);
    }
}

static void quick_sort_rec(i32 *a, i32 low, i32 high)
{
    if (low < high)
    {
        i32 p = partition(a, low, high);
        quick_sort_rec(a, low, p);
        quick_sort_rec(a, p + 1, high);
    }
}

void quick_sort(i32 *arr, i32 length)
{
    quick_sort_rec(arr, 0, length - 1);
}
