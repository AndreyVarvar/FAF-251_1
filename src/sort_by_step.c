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


i32 heap_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->i = 1;
            sd->j = 1;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            if (arr[indices[sd->i]] > arr[indices[(sd->i - 1)/2]])
            {
                sd->j = sd->i;
                while (arr[indices[sd->j]] > arr[indices[(sd->j - 1)/2]])
                {
                    SWAP(i32, indices + sd->j, indices + (sd->j - 1)/2);
                    sd->j = (sd->j - 1)/2;
                }
            }
            sd->i++;
            if (sd->i >= sd->length) 
            {
                sd->i = sd->length - 1;
                sd->j = 0;
                sd->phase = 2;
            }
            return 0;
        }
        case 2: {
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
            if (sd->i <= 0) sd->phase = 3;
            return 0;
        } break;
        case 3: {
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

// a is the array, i is the indices array.
static i32 median_of_three_index(i32 *a, i32 *i, i32 low, i32 mid, i32 high)
{
    // Whoever made this function I will find you.
    if ((a[i[low]] <= a[i[mid]] && a[i[mid]] <= a[i[high]]) || (a[i[high]] <= a[i[mid]] && a[i[mid]] <= a[i[low]]))
        return mid;
    if ((a[i[mid]] <= a[i[low]] && a[i[low]] <= a[i[high]]) || (a[i[high]] <= a[i[low]] && a[i[low]] <= a[i[mid]]))
        return low;
    return high;
}

i32 partition(i32 *arr, i32 *indices, i32 low, i32 high)
{
    i32 x = arr[indices[high]];
    i32 i = (low - 1);

    for (i32 j = low; j <= high - 1; j++) {
        if (arr[indices[j]] <= x) {
            i++;
            SWAP(i32, indices + i, indices + j);
        }
    }
    SWAP(i32, indices + i + 1, indices + high);
    return (i + 1);
}

static i32 quick_sort_step_rec(i32 *arr, i32 *indices, SortData *sd)
{
    switch (sd->phase) {
        case 0: {
            sd->high = sd->length - 1;
            sd->low = 0;
            sd->top = -1;
            sd->stack = malloc(2 * sd->length * sizeof(i32));
            sd->stack[++sd->top] = sd->low;
            sd->stack[++sd->top] = sd->high;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            sd->high = sd->stack[sd->top--];
            sd->low = sd->stack[sd->top--];

            i32 p = partition(arr, indices, sd->low, sd->high);

            if (p - 1 > sd->low) {
                sd->stack[++sd->top] = sd->low;
                sd->stack[++sd->top] = p - 1;
            }

            if (p + 1 < sd->high) {
                sd->stack[++sd->top] = p + 1;
                sd->stack[++sd->top] = sd->high;
            }

            if (sd->top < 0) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            sd->high = 0;
            sd->low = 0;
            sd->top = 0;
            free(sd->stack);
            sd->stack = NULL;
            sd->phase = 0;
            return 1;
        }
    }
}

i32 quick_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    return quick_sort_step_rec(arr, indices, sd);
}

i32 radix_sort_step(i32 *restrict arr, i32 *indices, SortData *sd)
{
    switch (sd->phase)
    {
        case 0: {
            if (sd->length <= 1)
            {
                sd->phase = 0;
                return 0;
            }

            sd->temp = aligned_alloc(64, sd->length * sizeof(i32));

            if (!sd->temp)
            {
                sd->phase = 0;
                return 0;
            }

            // Flip sign bit to handle signed i32s
            for (i32 i = 0; i < sd->length; i++)
                arr[i] ^= 0x80000000;

            sd->in = arr;
            sd->out = sd->temp;

            sd->misc = 256;
            sd->count = malloc(sd->misc * sizeof(i32));
            sd->i = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            memset(sd->count, 0, sd->misc * sizeof(i32));
            i32 shift = sd->i * 8;

            // Count digits
            for (i32 i = 0; i < sd->length; i++)
                sd->count[(sd->in[indices[i]] >> shift) & 0xFF]++;

            // Prefix sum
            i32 sum = 0;
            for (i32 i = 0; i < sd->misc; i++)
            {
                i32 t = sd->count[i];
                sd->count[i] = sum;
                sum += t;
            }

            // Stable scatter
            for (i32 i = 0; i < sd->length; i++)
            {
                i32 d = (sd->in[indices[i]] >> shift) & 0xFF;
                sd->out[sd->count[d]++] = indices[i];
            }

            // Swap buffers
            i32 *tmp_ptr = sd->in;
            sd->in = sd->out;
            sd->out = tmp_ptr;

            sd->i++;
            if (sd->i >= 4) sd->phase = 2;
            return 0;
        } break;
        case 2: {
            // If final data is in tmp, copy back once
            if (sd->in != arr)
                memcpy(indices, sd->in, sd->length * sizeof(i32));

            // Restore sign bit
            for (i32 i = 0; i < sd->length; i++)
                arr[i] ^= 0x80000000;

            sd->phase = 3;
            return 0;
        } break;
        case 3: {
            free(sd->temp);
            sd->temp = NULL;
            free(sd->count);
            sd->count = NULL;
            sd->phase = 0;
            return 1;
        }
    }
}

static void move_to_front(i32 *arr, i32 src, i32 dst)
{
    i32 temp = arr[src];
    for(i32 i = src; i > dst; --i)
        arr[i] = arr[i - 1];
    arr[dst] = temp;
}

i32 kind_stalin_sort_step(i32 *arr, i32 *indices, SortData *sd)
{
    switch(sd->phase) {
        case 0: {
            sd->i = 0;
            sd->j = 0;
            sd->misc = 0;
            sd->phase = 1;
            return 0;
        } break;
        case 1: {
            if (sd->i < sd->length - 1 - sd->j)
            {
                if(arr[indices[sd->i]] > arr[indices[sd->i + 1]])
                {
                    move_to_front(indices, sd->i + 1, sd->misc);
                    ++sd->misc;
                }
                sd->i++;
            } else {
                if(sd->misc == 0) 
                {
                    sd->phase = 2;
                    return 0;
                }
                sd->misc = 0;
                sd->i = 0;
                ++sd->j;
            }
            return 0;
        } break;
        case 2: {
            sd->i = 0;
            sd->j = 0;
            sd->misc = 0;
            sd->phase = 0;
            return 1;
        }
    }
}
