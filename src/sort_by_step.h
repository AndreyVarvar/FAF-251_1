#ifndef SORT_BY_STEP_H
#define SORT_BY_STEP_H

#include <stdlib.h>
#include <string.h>

#include "base.h"

// All hail the struct monolith
typedef struct SortData
{
    i32 phase; // All important phase var, don't you dare touch it or I will mince you.
    i32 i;
    i32 j;
    i32 misc; // For whatever reasons you may have ;)

    i32 gap; // Shell sort demands another variable

    i32 min_run; // TIM SORT WANTS MORE
    i32 runs_len;
    i32 length;

    i32 high; // MMMOOOOOOOOOORRRREEEE FFFOOORR QUICCCKK SOORTT
    i32 low;
    i32 top;

    i32 pass;

    i32 new_length;
    i32 current_element;
    i32 stalin_index;

    i32 *in;
    i32 *out;
    i32 *count;
    i32 *temp; // MMOOOORREE
    i32 *stack;
    i32 (*runs)[2];
} SortData;

typedef i32 (*step_sort_function)(i32 *arr, i32 *indices, SortData *sort_data);

i32 selection_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 insertion_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 bubble_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 shell_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 merge_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 heap_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 tim_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 quick_sort_step(i32 *arr, i32 *indices, SortData *sd);
i32 radix_sort_step(i32 *restrict arr, i32 *indices, SortData *sd);
i32 kind_stalin_sort_step(i32 *arr, i32 *indices, SortData *sd);
i32 is_sorted_by(i32 *arr, i32 *indices, i32 length);

#endif
