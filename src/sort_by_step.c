#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "base.h"
#include "utils.h"
#include "sort_by_step.h"

i32 selection_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            sd->misc = sd->i;
            sd->j = sd->i + 1;

            while (sd->j < sd->length)
            {
                if (arr[indices[sd->j]] < arr[indices[sd->misc]])
                {
                    sd->misc = sd->j;
                }
                sd->j++;
            }

            if (sd->misc != sd->i)
            {
                SWAP(i32, indices + sd->i, indices + sd->misc);
            }

            sd->i++;
            if (sd->i >= sd->length - 1) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 0;
            return 1;
        }
    }
}

i32 insertion_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->misc = 0;
            sd->i = 1;
            sd->j = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            sd->misc = indices[sd->i];
            sd->j = sd->i - 1;

            while (sd->j >= 0 && arr[indices[sd->j]] > arr[sd->misc])
            {
                indices[sd->j + 1] = indices[sd->j];
                sd->j -= 1;
            }

            indices[sd->j + 1] = sd->misc;
            sd->i++;
            if (sd->i > sd->length) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 0;
            return 1;
        }
    }
}

i32 bubble_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            sd->misc = 0;
            sd->j = 0;

            while (sd->j < sd->length - sd->i - 1)
            {
                if (arr[indices[sd->j]] > arr[indices[sd->j + 1]])
                {
                    SWAP(i32, indices + sd->j, indices + sd->j + 1);
                    sd->misc = 1;
                }
                sd->j++;
            }

            if (!sd->misc)
            {
                sd->i = sd->length - 1;
            }

            sd->i++;
            if (sd->i >= sd->length - 1) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 0;
            return 1;
        }
    }
}

i32 shell_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->gap = sd->length/2;
            sd->misc = 0;
            sd->i = sd->gap;
            sd->j = 2;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {

            if (sd->i < sd->length)
            {
                sd->misc = indices[sd->i];
                sd->j = sd->i;
                while (sd->j >= sd->gap && arr[indices[sd->j - sd->gap]] > arr[sd->misc])
                {
                    indices[sd->j] = indices[sd->j - sd->gap];
                    sd->j -= sd->gap;
                }
                indices[sd->j] = sd->misc;
                sd->i++;
            } else {
                sd->gap /= 2;
                sd->i = sd->gap;
            }

            if (sd->gap == 0) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->gap = 0;
            sd->misc = 0;
            sd->i = 0;
            sd->j = 0;
            sd->phase = 0;
            return 1;
        }
    }
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

i32 merge_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->i = 1;
            sd->j = 0;
            sd->temp = malloc(sd->length * sizeof(i32));
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            if (sd->j < sd->length - 1)
            {
                i32 mid = min(sd->j + sd->i - 1, sd->length-1);
                i32 rightEnd = min(sd->j + 2*sd->i - 1, sd->length-1);
                merge(arr, indices, sd->temp, sd->j, mid, rightEnd);
                sd->j += 2 * sd->i;
            } else {
                sd->j = 0;
                sd->i *= 2;
            }
            if (sd->i > sd->length - 1) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->i = 0;
            sd->j = 0;
            free(sd->temp);
            sd->temp = NULL;
            sd->phase = 0;
            return 1;
        }
    }
}

static void build_max_heap(i32 *arr, i32 *indices, SortData *sd)
{
    for (i32 i = 1; i < sd->length; i++)
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

i32 heap_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            build_max_heap(arr, indices, sd);
            sd->i = sd->length - 1;
            sd->j = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            SWAP(i32, indices, indices + sd->i);
            sd->j = 0;
            i32 index;

            do {
                index = 2*sd->j + 1;
                if (index  < sd->i - 1 && arr[indices[index]] < arr[indices[index + 1]]) index++;
                if (index < sd->i && arr[indices[sd->j]] < arr[indices[index]])
                {
                    SWAP(i32, indices + sd->j, indices + index);
                }
                sd->j = index;
            } while (index < sd->i);

            sd->i--;
            if (sd->i <= 0) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->i = 0;
            sd->j = 0;
            sd->phase = 0;
            return 1;
        }
    }
}

static i32 find_run(i32* arr, i32 *indices, i32 start, i32 length)
{
    i32 end = start + 1;
    if (end == length)
    {
        return end;
    }
    if (arr[indices[end]] < arr[indices[start]])
    {
        while (end < length && arr[indices[end]] < arr[indices[end-1]])
        {
            end++;
        }
        reverse(indices, start, end);
    }
    else
    {
        while (end < length && arr[indices[end]] >= arr[indices[end-1]])
        {
            end++;
        }
    }
    return end;
}

static void insertion_sort_for_tim(i32 *arr, i32 *indices, i32 start, i32 end) {
    for (i32 i = start + 1 ; i <= end; i++)
    {
        i32 key = indices[i];
        i32 j = i - 1 ;
        while (j >= start && arr[indices[j]] > arr[key])
        {
            indices[j+1] = indices[j];
            j = j - 1;
        }
        indices[j+1] = key;
    }
}

i32 tim_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->i = 0;
            sd->min_run = 32;
            sd->temp = malloc(sd->length * sizeof(i32));
            sd->runs = malloc(128 * sizeof(i32[2]));
            sd->runs_len = 0;
            sd->phase++;
            return 0;
        } break;
        case 1: {
            i32 run_end = find_run(arr, indices, sd->i, sd->length);
            i32 run_len = run_end - sd->i;
            if (run_len < sd->min_run)
            {
                i32 end = (sd->i + sd->min_run < sd->length) ? sd->i + sd->min_run : sd->length;
                insertion_sort_for_tim(arr, indices, sd->i, end - 1);
                run_end = end;
            }
            sd->runs_len++;
            sd->runs[sd->runs_len-1][0] = sd->i;
            sd->runs[sd->runs_len-1][1] = run_end;
            sd->i = run_end;

            if (sd->runs_len > 1) sd->phase = 2;
            if (sd->i >= sd->length) sd->phase = 3;
            return 0;
        } break;
        case 2: {
            i32 l1 = sd->runs[sd->runs_len - 2][0];
            i32 r1 = sd->runs[sd->runs_len - 2][1];
            i32 l2 = sd->runs[sd->runs_len - 1][0];
            i32 r2 = sd->runs[sd->runs_len - 1][1];

            i32 len1 = r1 - l1;
            i32 len2 = r2 - l2;

            if (len1 <= len2)
            {
                merge(arr, indices, sd->temp, l1, r1 - 1, r2 - 1);
                sd->runs_len--;
                sd->runs[sd->runs_len - 1][0] = l1;
                sd->runs[sd->runs_len - 1][1] = r2;
            }
            else sd->phase = 1;
            if (sd->runs_len <= 1) sd->phase = 1;
            return 0;
        } break;
        case 3: {
            while (sd->runs_len > 1)
            {
                i32 l1 = sd->runs[sd->runs_len - 2][0];
                i32 r1 = sd->runs[sd->runs_len - 2][1];
                i32 r2 = sd->runs[sd->runs_len - 1][1];
                merge(arr, indices, sd->temp, l1, r1 - 1, r2 - 1);
                sd->runs_len--;
                sd->runs[sd->runs_len - 1][0] = l1;
                sd->runs[sd->runs_len - 1][1] = r2;
            }
            sd->phase = 4;
            return 0;
        } break;
        case 4: {
            free(sd->temp);
            sd->temp = NULL;
            free(sd->runs);
            sd->i = 0;
            sd->runs = NULL;
            sd->runs_len = 0;
            sd->phase = 0;
            return 1;
        }
    }
}
