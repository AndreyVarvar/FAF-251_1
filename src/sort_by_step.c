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

static void build_max_heap(i32 *arr, i32 *indices, SortData *sort_data)
{
    for (i32 i = 1; i < sort_data->length; i++)
    {
        if (arr[indices[i]] > arr[indices[(i - 1)/2]])
        {
            i32 j = i;
            while (arr[indices[j]] > arr[indices[(j - 1)/2]])
            {
                SWAP(i32, indices + j, indices + (j - 1)/2);
                j = (j - 1)/2;
            }
        }
    }
}

i32 heap_sort_step(i32 *arr, i32 *indices, SortData *sort_data)
{
    if (sort_data->i == -1)
    {
        sort_data->i = sort_data->length - 1;
        sort_data->j = 0;
        build_max_heap(arr, indices, sort_data);
    }

    if (sort_data->i <= 0)
    {
        sort_data->i = -1;
        sort_data->j = -1;
        return 1;
    }

    SWAP(i32, indices, indices + sort_data->i);
    sort_data->j = 0;
    i32 index;

    do {
        index = 2*sort_data->j + 1;
        if (index  < sort_data->i - 1 && arr[indices[index]] < arr[indices[index + 1]]) index++;
        if (index < sort_data->i && arr[indices[sort_data->j]] < arr[indices[index]])
        {
            SWAP(i32, indices + sort_data->j, indices + index);
        }
        sort_data->j = index;
    } while (index < sort_data->i);

    sort_data->i--;

    return 0;
}

static i32 find_run(i32* arr, i32 start, i32 length)
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

static void insertion_sort_for_tim(i32 *arr, i32 start, i32 end) {
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
            insertion_sort_for_tim(arr, i, end - 1);
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
        // i32 l2 = runs[runs_len - 1][0];
        i32 r2 = runs[runs_len - 1][1];
        merge(arr, tmp, l1, r1 - 1, r2 - 1);
        runs_len--;
        runs[runs_len - 1][0] = l1;
        runs[runs_len - 1][1] = r2;
    }
    free(tmp);
}
