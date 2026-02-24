#include <stdlib.h>

#include "sorts.h"
#include "../base.h"
#include "../utils.h"

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
