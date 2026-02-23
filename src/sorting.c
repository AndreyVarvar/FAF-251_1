#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "base.h"
#include "sorting.h"

void selection_sort(i32 *arr, i32 length)
{
    i32 min_idx;
    for (i32 i = 0; i < length - 1; i++)
    {
        min_idx = i;
        for (i32 j = i + 1; j < length; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            SWAP(i32, arr + i, arr + min_idx);
        }
    }
}

void insertion_sort(i32 *arr, i32 length)
{
    i32 key, j;
    for (i32 i = 1; i <= length; i++) 
    {
        key = arr[i];
        j = i - 1 ;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

void bubble_sort(i32 *arr, i32 length)
{
    i32 swapped, temp;
    for (i32 i = 0; i < length-1; i++)
    {
        swapped = 0;
        for (i32 j = 0; j < length-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                SWAP(i32, arr + j, arr + j + 1);
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void shell_sort(i32 *arr, i32 length)
{
    i32 temp, j;
    for (i32 gap = length / 2; gap > 0; gap /= 2)
    {
        for (i32 i = gap; i < length; i++)
        {
            temp = arr[i];
            j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void merge(i32 *arr, i32 *temp, i32 left, i32 mid, i32 right)
{
    i32 i = left;
    i32 j = mid + 1;
    i32 k = left;
    i32 n1 = mid - left + 1;
    i32 n2 = right - mid;

    for (i32 x = left; x <= right; x++)
    {
        temp[x] = arr[x];
    }

    while (i <= mid && j <= right)
    {
        if (temp[i] <= temp[j])
        {
            arr[k++] = temp[i++];
        }
        else
        {
            arr[k++] = temp[j++];
        }
    }

    while (i <= mid)
    {
        arr[k++] = temp[i++];
    }
}

void merge_sort_rec(i32 *arr, i32 *temp, i32 left, i32 right)
{
    if (left < right) {
        i32 mid = left + (right - left) / 2;

        merge_sort_rec(arr, temp, left, mid);
        merge_sort_rec(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);
    }
}

void merge_sort(i32 *arr, i32 length)
{
    i32 *temp = malloc((length) * sizeof(i32));
    merge_sort_rec(arr, temp, 0, length - 1);
    free(temp);
}

void heapify(i32 *arr, i32 length, i32 i)
{
    i32 max = i;
    i32 left = 2*i + 1;
    i32 right = 2*i + 2;

    if (left < length && arr[left] > arr[max])
    {
        max = left;
    }
    if (right < length && arr[right] > arr[max])
    {
        max = right;
    }
    if (max != i)
    {
        SWAP(i32, arr + i, arr + max);
        heapify(arr, length, max);
    }
}

void heap_sort(i32 *arr, i32 length)
{
    for (i32 i = length/2; i >= 0; i--)
    {
        heapify(arr, length, i);
    }
    for (i32 i = length - 1; i > 0; i--)
    {
        i32 temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void tim_insertion_sort(i32 *arr, i32 start, i32 end)
{
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

void reverse(i32 *arr, i32 start, i32 end)
{
    for (i32 i = 0; i < (start + end)/2 - start; i++)
    {
        SWAP(i32, arr + start + i, arr + end - i);
    }
}

i32 find_run(i32* arr, i32 start, i32 length)
{
    i32 end = start + 1;
    if (end == length)
    {
        return end;
    }
    if (arr[end] < arr[start])
    {
        while (end < length && arr[end] < arr[end-1])
        {
            end++;
        }
        reverse(arr, start, end);
    }
    else
    {
        while (end < length && arr[end] >= arr[end-1])
        {
            end++;
        }
    }
    return end;
}

void tim_sort(i32 *arr, i32 length)
{
    i32 min_run = 32;
    i32 *temp = malloc(length * sizeof(i32));
    i32 runs[128][2];
    i32 runs_len = 0;

    i32 i = 0;
    while (i < length)
    {
        i32 run_end = find_run(arr, i, length);
        i32 run_len = run_end - i;
        if (run_len < min_run)
        {
            i32 end = (i + min_run < length) ? i + min_run : length;
            tim_insertion_sort(arr, i, end - 1);
            run_end = end;
        }
        runs_len++;
        runs[runs_len-1][0] = i;
        runs[runs_len-1][1] = run_end;
        i = run_end;

        while (runs_len > 1)
        {
            i32 l1 = runs[runs_len - 2][0];
            i32 r1 = runs[runs_len - 2][1];
            i32 l2 = runs[runs_len - 1][0];
            i32 r2 = runs[runs_len - 1][1];

            i32 len1 = r1 - l1;
            i32 len2 = r2 - l2;

            if (len1 <= len2)
            {
                merge(arr, temp, l1, r1 - 1, r2 - 1);
                runs_len--;
                runs[runs_len - 1][0] = l1;
                runs[runs_len - 1][1] = r2;
            }
            else break;
        }
    }
    while (runs_len > 1)
    {
        i32 l1 = runs[runs_len - 2][0];
        i32 r1 = runs[runs_len - 2][1];
        i32 l2 = runs[runs_len - 1][0];
        i32 r2 = runs[runs_len - 1][1];
        merge(arr, temp, l1, r1 - 1, r2 - 1);
        runs_len--;
        runs[runs_len - 1][0] = l1;
        runs[runs_len - 1][1] = r2;
    }
    free(temp);
}

static void move_to_front(i32 *arr, i32 size, i32 src, i32 dst)
{
    i32 temp = arr[src];
    for (i32 i = src; i > dst; --i)
    {
        arr[i] = arr[i - 1];
    }
    arr[dst] = temp;
}

void stalin_sort(i32 *arr, i32 length)
{
    i32 j = 0;
    while (1)
    {
        i32 moved = 0;

        for (i32 i = 0; i < length - 1 - j; ++i)
        {
            if(arr[i] > arr[i + 1])
            {
                move_to_front(arr, length, i + 1, moved);
                ++moved;
            }
        }

        ++j;
        if(moved == 0)
            break;
    }
}

i32 partition(i32 *arr, i32 low, i32 high)
{
    i32 p = arr[low];
    i32 i = low;
    i32 j = high;

    while(i < j)
    {

        while(arr[i] <= p && i <= high - 1)
        {
            i++;
        }
        while(arr[j] > p && j >= low + 1)
        {
            j--;
        }
        if(i < j)
        {
            SWAP(i32, arr + i, arr + j);
        }
    }
    SWAP(i32, arr + low, arr + j);
    return j;
}

void quick_sort(i32 *arr, i32 low, i32 high)
{
    if(low < high)
    {
        i32 cut = partition(arr, low, high);
        quick_sort(arr, low, cut - 1);
        quick_sort(arr, cut + 1, high);
    }
}


void print_i32_arr(i32 *arr, i32 length)
{
    printf("{");
    for (i32 i = 0; i < length; i++)
    {
        printf("%d", arr[i]);

        if (i != length-1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

void benchmark(char* sort_flag)
{
    i32 size = 1000000;
    i32 *arr = malloc(size * sizeof(i32));

    for (i32 i = 0; i < size; i++)
    {
        i32 sign = (rand() % 2 == 1) ? 1 : -1;
        arr[i] = (sign) * rand();
    }

    clock_t start = clock();
    if (strcmp("-s", sort_flag) == 0)
    {
        printf("Selection sort:\n");
        selection_sort(arr, size);
    }
    else if (strcmp("-i", sort_flag) == 0)
    {
        printf("Insertion sort:\n");
        insertion_sort(arr, size);
    }
    else if (strcmp("-b", sort_flag) == 0)
    {
        printf("Bubble sort:\n");
        bubble_sort(arr, size);
    }
    else if (strcmp("sh", sort_flag) == 0)
    {
        printf("Shell sort:\n");
        shell_sort(arr, size);
    }
    else if (strcmp("-m", sort_flag) == 0)
    {
        printf("Merge sort:\n");
        merge_sort(arr, size);
    }
    else if (strcmp("-h", sort_flag) == 0)
    {
        printf("Heap sort:\n");
        heap_sort(arr, size);
    }
    else if(strcmp("-t", sort_flag) == 0)
    {
        printf("Tim sort:\n");
        tim_sort(arr, size);
    }
    else if(strcmp("-st", sort_flag) == 0)
    {
        printf("Stalin sort:\n");
        stalin_sort(arr, size);
    }
    else if(strcmp("-q", sort_flag) == 0)
    {
        printf("Quick sort:\n");
        quick_sort(arr, 0, size-1);
    }
    //add if new sorts
    clock_t end = clock();
    i32 check = 1;
    for (i32 i = 1; i < size; i++)
    {
        if (arr[i-1] > arr[i])
        {
            check = 0;
            break;
        }
    }
    if (check)
    {
        printf("Sort successful.\nTime: %lf\n\n", (double)(end-start) / CLOCKS_PER_SEC);
    }
    else
    {
        printf("Sort unsuccessful.\n");
    }
    free(arr);
}
