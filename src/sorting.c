#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "base.h"
#include "sorting.h"

void selection_sort(i32 *arr, i32 length) {
    i32 i, j, min_idx, temp;
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

void insertion_sort(i32 *arr, i32 start, i32 end) {
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

void bubble_sort(i32 *arr, i32 length) {
    for (i32 i = 0; i < length-1; i++)
    {
        i32 swapped = 0;
        for (i32 j = 0; j < length-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                i32 tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

void shell_sort(i32 *arr, i32 length) {
    for (i32 gap = length / 2; gap > 0; gap /= 2) {
        for (i32 i = gap; i < length; i++) {
            i32 temp = arr[i];
            i32 j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
void merge_sort(i32 *arr, i32 left, i32 right)
{
    i32 *tmp = malloc((right - left + 1) * sizeof(i32));
    merge_sort_rec(arr, tmp, left, right);
    free(tmp);
}

void merge_sort_rec(i32 *arr, i32 *tmp, i32 left, i32 right) {
    if (left < right) {
        i32 mid = left + (right - left) / 2;

        merge_sort_rec(arr, tmp, left, mid);
        merge_sort_rec(arr, tmp, mid + 1, right);

        merge(arr, tmp, left, mid, right);
    }
}

void merge(i32 *arr, i32 *tmp, i32 left, i32 mid, i32 right) {
    i32 i = left;
    i32 j = mid + 1;
    i32 k = left;
    i32 n1 = mid - left + 1;
    i32 n2 = right - mid;

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

void heap_sort(i32 *arr, i32 length)
{
    for (i32 i = length/2; i >= 0; i--)
    {
        heapify(arr, length, i);
    }
    for (i32 i = length - 1; i > 0; i--)
    {
        i32 tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
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
        i32 tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, length, max);
    }
}

void tim_sort(i32 *arr, i32 length)
{
    i32 min_run = 32;
    i32 *tmp = malloc(length * sizeof(i32));
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
            insertion_sort(arr, i, end - 1);
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
                merge(arr, tmp, l1, r1 - 1, r2 - 1);
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
        merge(arr, tmp, l1, r1 - 1, r2 - 1);
        runs_len--;
        runs[runs_len - 1][0] = l1;
        runs[runs_len - 1][1] = r2;
    }
    free(tmp);
}

static void move_to_front(i32 *a, i32 size, i32 src, i32 dst)
{
    i32 temp = a[src];
    for(i32 i = src; i > dst; --i)
        a[i] = a[i - 1];
    a[dst] = temp;
}

void stalin_sort(i32 *a, i32 n)
{
    i32 j = 0;
    while(1)
    {
        i32 moved = 0;

        for(i32 i = 0; i < n - 1 - j; ++i)
        {
            if(a[i] > a[i + 1])
            {
                move_to_front(a, n, i + 1, moved);
                ++moved;
            }
        }

        ++j;
        if(moved == 0)
            break;
    }
}

i32 *cruel_stalin_sort(i32 *arr, i32 *length)
{
    if (*length <= 1)
        return arr;   // nothing to do

    i32 new_length = 1;
    i32 current_element = arr[0];
    for (i32 i = 1; i < *length; ++i)
        if (arr[i] >= current_element)
        {
            current_element = arr[i];
            new_length++;
        }

    i32 *new_arr = malloc(new_length * sizeof *new_arr);

    current_element = arr[0];
    new_arr[0] = current_element;

    i32 stalin_index = 1;
    for (i32 i = 1; i < *length; ++i)
        if (arr[i] >= current_element)
        {
            new_arr[stalin_index] = arr[i];
            current_element = arr[i];
            stalin_index++;
        }

    free(arr);
    *length = new_length;
    return new_arr;
}

//It might be a good idea to use this for the other sort functions that swap variables
//just to reduce the amount of code
void swap(i32* a, i32* b)
{
    i32 temp = *a;
    *a = *b;
    *b = temp;
}

i32 partition(i32 *a, i32 low, i32 high)
{
    i32 p = a[low];
    i32 i = low;
    i32 j = high;

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

void quick_sort(i32 *a, i32 low, i32 high)
{
    if(low < high)
    {
        i32 cut = partition(a, low, high);
        quick_sort(a, low, cut - 1);
        quick_sort(a, cut + 1, high);
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

void print_i32_arr(i32 *arr, i32 length) {
    printf("{");
    for (i32 i = 0; i < length; i++) {
        printf("%d", arr[i]);

        if (i != length-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void reverse(i32 *arr, i32 start, i32 end)
{
    for (i32 i = 0; i < (start + end)/2 - start; i++)
    {
        i32 tmp = arr[start + i];
        arr[start + i] = arr[end - i];
        arr[end - i] = tmp;
    }
}

void benchmark(char* option)
{
    printf("Started %s sort.\n", option);
    i32 size = 1000000;
    i32 *arr = malloc(size * sizeof(i32));
    for (i32 i = 0; i < size; i++)
    {
        i32 sign = (rand() % 2 == 1) ? 1 : -1;
        arr[i] = (sign) * rand();
    }
    clock_t start = clock();
    if      (strcmp("selection", option) == 0)
    {
        selection_sort(arr, size);
    }
    else if (strcmp("insertion", option) == 0)
    {
        insertion_sort(arr, 0, size);
    }
    else if (strcmp("bubble", option) == 0)
    {
        bubble_sort(arr, size);
    }
    else if (strcmp("shell", option) == 0)
    {
        shell_sort(arr, size);
    }
    else if (strcmp("merge", option) == 0)
    {
        merge_sort(arr, 0, size-1);
    }
    else if (strcmp("heap", option) == 0)
    {
        heap_sort(arr, size);
    }
    else if(strcmp("tim", option) == 0)
    {
        tim_sort(arr, size);
    }
    else if(strcmp("stalin", option) == 0)
    {
        arr = cruel_stalin_sort(arr, &size);
    }
    else if(strcmp("quick", option) == 0)
    {
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
        printf("%s sort successfull.\nTime: %lf\n\n", option, (double)(end-start) / CLOCKS_PER_SEC);
    }
    else
    {
        printf("%s sort unsuccessfull.\n", option);
    }
    free(arr);
}
