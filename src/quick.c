#include "sorts.h"
#include "utils.h"


static int partition(int *a, int low, int high)
{
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