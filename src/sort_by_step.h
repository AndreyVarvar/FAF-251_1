#ifndef SORT_BY_STEP_H
#define SORT_BY_STEP_H

#include "base.h"

typedef struct SortData
{
    i32 i;
    i32 j;
    i32 length;
    i32 key;
} SortData;

// typedef struct SwapIndices
// {
//     i32 i
// }

i32 selection_sort_step(i32 *arr, i32 *indices, SortData *sort_data);
i32 insertion_sort_step(i32 *arr, i32 *indices, SortData *sort_data);

#endif
