#include "sorts.h"
#include "utils.h"

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

    // Move pivot to start
    swap(&a[low], &a[pivot_index]);

    int p = a[low];
    int i = low;
    int j = high;

    while(i < j)
    {

        while(a[i] <= p && i <= high - 1)
        {
            i++;
        }
        while(a[j] > p && j >= low + 1)
        {
            j--;
        }
        if(i < j)
        {
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[low], &a[j]);
    return j;
}

static void quick_sort_rec(int *a, int low, int high)
{
    if(low < high)
    {
        int cut = partition(a, low, high);
        quick_sort_rec(a, low, cut - 1);
        quick_sort_rec(a, cut + 1, high);
    }
}

void quick_sort(int *arr, int length)
{
    quick_sort_rec(arr, 0, length - 1);
}