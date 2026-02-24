#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "base.h"
#include "utils.h"
#include "sort_by_step.h"

i32 selection_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->misc < 0) {
        sort_data->misc = 0;
        sort_data->i = 0;
        sort_data->j = 0;
    }

    if (sort_data->i >= sort_data->length - 1) 
    {
        sort_data->misc = -1;
        sort_data->i = -1;
        sort_data->j = -1;
        return 1;
    }

    while (sort_data->j < sort_data->length)
    {
        if (arr[indices[sort_data->j]] < arr[indices[sort_data->misc]])
        {
            sort_data->misc = sort_data->j;
        }
        sort_data->j++;
    }

    if (sort_data->misc != sort_data->i)
    {
        SWAP(i32, indices + sort_data->i, indices + sort_data->misc);
    }

    sort_data->i++;
    sort_data->misc = sort_data->i;
    sort_data->j = sort_data->i + 1;
    return 0;
}

i32 insertion_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->misc < 0) {
        sort_data->misc = 0;
        sort_data->i = 1;
        sort_data->j = 0;
    }

    if (sort_data->i > sort_data->length)
    {
        sort_data->misc = -1;
        sort_data->i = -1;
        sort_data->j = -1;
        return 1;
    }

    sort_data->misc = indices[sort_data->i];
    sort_data->j = sort_data->i - 1;

    while (sort_data->j >= 0 && arr[indices[sort_data->j]] > arr[sort_data->misc])
    {
        indices[sort_data->j + 1] = indices[sort_data->j];
        sort_data->j -= 1;
    }

    indices[sort_data->j + 1] = sort_data->misc;
    sort_data->i++;
    return 0;
}

i32 bubble_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->misc < 0) {
        sort_data->misc = 0;
        sort_data->i = 0;
        sort_data->j = 0;
    }

    if (sort_data->i >= sort_data->length - 1)
    {
        sort_data->misc = -1;
        sort_data->i = -1;
        sort_data->j = -1;
        return 1;
    }

    sort_data->misc = 0;
    sort_data->j = 0;

    while (sort_data->j < sort_data->length - sort_data->i - 1)
    {
        if (arr[indices[sort_data->j]] > arr[indices[sort_data->j + 1]])
        {
            SWAP(i32, indices + sort_data->j, indices + sort_data->j + 1);
            sort_data->misc = 1;
        }
        sort_data->j++;
    }

    if (!sort_data->misc)
    {
        sort_data->i = sort_data->length - 1;
    }

    sort_data->i++;
    return 0;
}

i32 shell_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->gap < 0) {
        sort_data->gap = sort_data->length/2;
        sort_data->misc = 0;
        sort_data->i = sort_data->gap;
        sort_data->j = 2;
    }

    if (sort_data->gap == 0) {
        sort_data->gap = -1;
        sort_data->misc = -1;
        sort_data->i = -1;
        sort_data->j = -1;
        return 1;
    }

    if (sort_data->i < sort_data->length)
    {
        sort_data->misc = indices[sort_data->i];
        sort_data->j = sort_data->i;
        while (sort_data->j >= sort_data->gap && arr[indices[sort_data->j - sort_data->gap]] > arr[sort_data->misc])
        {
            indices[sort_data->j] = indices[sort_data->j - sort_data->gap];
            sort_data->j -= sort_data->gap;
        }
        indices[sort_data->j] = sort_data->misc;
        sort_data->i++;
    } else
    {
        sort_data->gap /= 2;
        sort_data->i = sort_data->gap;
    }

    return 0;
}

static void merge(i32 *arr, i32 *indices, i32 *tmp, i32 left, i32 mid, i32 right)
{
    i32 i = left;
    i32 j = mid + 1;
    i32 k = left;

    for (i32 x = left; x <= right; x++)
    {
        tmp[x] = indices[x];
    }

    while (i <= mid && j <= right)
    {
        if (arr[tmp[i]] <= arr[tmp[j]])
        {
            indices[k++] = tmp[i++];
        }
        else
        {
            indices[k++] = tmp[j++];
        }
    }

    while (i <= mid)
    {
        indices[k++] = tmp[i++];
    }
}

i32 merge_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->temp == NULL)
    {
        sort_data->i = 1;
        sort_data->j = 0;
        sort_data->temp = malloc(sort_data->length * sizeof(i32));
    }

    if (sort_data->i > sort_data->length - 1)
    {
        sort_data->i = -1;
        sort_data->j = -1;
        free(sort_data->temp);
        sort_data->temp = NULL;
        return 1;
    }

    if (sort_data->j < sort_data->length - 1)
    {
        i32 mid = min(sort_data->j + sort_data->i - 1, sort_data->length-1);
        i32 rightEnd = min(sort_data->j + 2*sort_data->i - 1, sort_data->length-1);
        merge(arr, indices, sort_data->temp, sort_data->j, mid, rightEnd);
        sort_data->j += 2 * sort_data->i;
    } else
    {
        sort_data->j = 0;
        sort_data->i *= 2;
    }

    return 0;
}
//
// void heapify(i32 *arr, i32 length, i32 i)
// {
//     i32 max = i;
//     i32 left = 2*i + 1;
//     i32 right = 2*i + 2;
//
//     if (left < length && arr[left] > arr[max])
//     {
//         max = left;
//     }
//     if (right < length && arr[right] > arr[max])
//     {
//         max = right;
//     }
//     if (max != i)
//     {
//         swap(arr + i, arr + max);
//         heapify(arr, length, max);
//     }
// }
//
// void heap_sort(i32 *arr, i32 length)
// {
//     for (i32 i = length/2; i >= 0; i--)
//     {
//         heapify(arr, length, i);
//     }
//     for (i32 i = length - 1; i > 0; i--)
//     {
//         i32 temp = arr[0];
//         arr[0] = arr[i];
//         arr[i] = temp;
//         heapify(arr, i, 0);
//     }
// }
//
// void tim_insertion_sort(i32 *arr, i32 start, i32 end)
// {
//     for (i32 i = start + 1 ; i <= end; i++) 
//     {
//         i32 key = arr[i];
//         i32 j = i - 1 ;
//         while (j >= start && arr[j] > key) 
//         {
//             arr[j+1] = arr[j];
//             j = j - 1;
//         }
//         arr[j+1] = key;
//     }
// }
//
// void reverse(i32 *arr, i32 start, i32 end)
// {
//     for (i32 i = 0; i < (start + end)/2 - start; i++)
//     {
//         swap(arr + start + i, arr + end - i);
//     }
// }
//
// i32 find_run(i32* arr, i32 start, i32 length)
// {
//     i32 end = start + 1;
//     if (end == length)
//     {
//         return end;
//     }
//     if (arr[end] < arr[start])
//     {
//         while (end < length && arr[end] < arr[end-1])
//         {
//             end++;
//         }
//         reverse(arr, start, end);
//     }
//     else
//     {
//         while (end < length && arr[end] >= arr[end-1])
//         {
//             end++;
//         }
//     }
//     return end;
// }
//
// void tim_sort(i32 *arr, i32 length)
// {
//     i32 min_run = 32;
//     i32 *temp = malloc(length * sizeof(i32));
//     i32 runs[128][2];
//     i32 runs_len = 0;
//
//     i32 i = 0;
//     while (i < length)
//     {
//         i32 run_end = find_run(arr, i, length);
//         i32 run_len = run_end - i;
//         if (run_len < min_run)
//         {
//             i32 end = (i + min_run < length) ? i + min_run : length;
//             tim_insertion_sort(arr, i, end - 1);
//             run_end = end;
//         }
//         runs_len++;
//         runs[runs_len-1][0] = i;
//         runs[runs_len-1][1] = run_end;
//         i = run_end;
//
//         while (runs_len > 1)
//         {
//             i32 l1 = runs[runs_len - 2][0];
//             i32 r1 = runs[runs_len - 2][1];
//             i32 l2 = runs[runs_len - 1][0];
//             i32 r2 = runs[runs_len - 1][1];
//
//             i32 len1 = r1 - l1;
//             i32 len2 = r2 - l2;
//
//             if (len1 <= len2)
//             {
//                 merge(arr, temp, l1, r1 - 1, r2 - 1);
//                 runs_len--;
//                 runs[runs_len - 1][0] = l1;
//                 runs[runs_len - 1][1] = r2;
//             }
//             else break;
//         }
//     }
//     while (runs_len > 1)
//     {
//         i32 l1 = runs[runs_len - 2][0];
//         i32 r1 = runs[runs_len - 2][1];
//         i32 l2 = runs[runs_len - 1][0];
//         i32 r2 = runs[runs_len - 1][1];
//         merge(arr, temp, l1, r1 - 1, r2 - 1);
//         runs_len--;
//         runs[runs_len - 1][0] = l1;
//         runs[runs_len - 1][1] = r2;
//     }
//     free(temp);
// }
//
// static void move_to_front(i32 *arr, i32 size, i32 src, i32 dst)
// {
//     i32 temp = arr[src];
//     for (i32 i = src; i > dst; --i)
//     {
//         arr[i] = arr[i - 1];
//     }
//     arr[dst] = temp;
// }
//
// void stalin_sort(i32 *arr, i32 length)
// {
//     i32 j = 0;
//     while (1)
//     {
//         i32 moved = 0;
//
//         for (i32 i = 0; i < length - 1 - j; ++i)
//         {
//             if(arr[i] > arr[i + 1])
//             {
//                 move_to_front(arr, length, i + 1, moved);
//                 ++moved;
//             }
//         }
//
//         ++j;
//         if(moved == 0)
//             break;
//     }
// }
//
// i32 partition(i32 *arr, i32 low, i32 high)
// {
//     i32 p = arr[low];
//     i32 i = low;
//     i32 j = high;
//
//     while(i < j)
//     {
//
//         while(arr[i] <= p && i <= high - 1)
//         {
//             i++;
//         }
//         while(arr[j] > p && j >= low + 1)
//         {
//             j--;
//         }
//         if(i < j)
//         {
//             swap(&arr[i], &arr[j]);
//         }
//     }
//     swap(&arr[low], &arr[j]);
//     return j;
// }
//
// void quick_sort(i32 *arr, i32 low, i32 high)
// {
//     if(low < high)
//     {
//         i32 cut = partition(arr, low, high);
//         quick_sort(arr, low, cut - 1);
//         quick_sort(arr, cut + 1, high);
//     }
// }
//
//
// void print_i32_arr(i32 *arr, i32 length)
// {
//     printf("{");
//     for (i32 i = 0; i < length; i++)
//     {
//         printf("%d", arr[i]);
//
//         if (i != length-1)
//         {
//             printf(", ");
//         }
//     }
//     printf("}\n");
// }
//
// void benchmark(char* sort_flag)
// {
//     i32 size = 1000;
//     i32 *arr = malloc(size * sizeof(i32));
//
//     for (i32 i = 0; i < size; i++)
//     {
//         i32 sign = (rand() % 2 == 1) ? 1 : -1;
//         arr[i] = (sign) * rand();
//     }
//
//     clock_t start = clock();
//     if (strcmp("-s", sort_flag) == 0)
//     {
//         printf("Selection sort:\n");
//         selection_sort(arr, size);
//     }
//     else if (strcmp("-i", sort_flag) == 0)
//     {
//         printf("Insertion sort:\n");
//         insertion_sort(arr, size);
//     }
//     else if (strcmp("-b", sort_flag) == 0)
//     {
//         printf("Bubble sort:\n");
//         bubble_sort(arr, size);
//     }
//     else if (strcmp("sh", sort_flag) == 0)
//     {
//         printf("Shell sort:\n");
//         shell_sort(arr, size);
//     }
//     else if (strcmp("-m", sort_flag) == 0)
//     {
//         printf("Merge sort:\n");
//         merge_sort(arr, size);
//     }
//     else if (strcmp("-h", sort_flag) == 0)
//     {
//         printf("Heap sort:\n");
//         heap_sort(arr, size);
//     }
//     else if(strcmp("-t", sort_flag) == 0)
//     {
//         printf("Tim sort:\n");
//         tim_sort(arr, size);
//     }
//     else if(strcmp("-st", sort_flag) == 0)
//     {
//         printf("Stalin sort:\n");
//         stalin_sort(arr, size);
//     }
//     else if(strcmp("-q", sort_flag) == 0)
//     {
//         printf("Quick sort:\n");
//         quick_sort(arr, 0, size-1);
//     }
//     //add if new sorts
//     clock_t end = clock();
//     i32 check = 1;
//     for (i32 i = 1; i < size; i++)
//     {
//         if (arr[i-1] > arr[i])
//         {
//             check = 0;
//             break;
//         }
//     }
//     if (check)
//     {
//         printf("Sort successful.\nTime: %lf\n\n", (double)(end-start) / CLOCKS_PER_SEC);
//     }
//     else
//     {
//         printf("Sort unsuccessful.\n");
//     }
//     free(arr);
// }
