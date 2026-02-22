#ifndef SORTING_H
#define SORTING_H

#include "base.h"

void selection_sort(i32 *arr, i32 length);
void insertion_sort(i32 *arr, i32 start, i32 end);
void bubble_sort(i32 *arr, i32 length);
void shell_sort(i32 *arr, i32 length);
// Merge sort
void merge_sort(i32 *arr, i32 left, i32 right);
void merge_sort_rec(i32 *arr, i32 *tmp, i32 left, i32 right);
void merge(i32 *arr, i32 *tmp, i32 left, i32 mid, i32 right);
// Heap sort
void heap_sort(i32 *arr, i32 lenght);
void heapify(i32 *arr, i32 length, i32 current);
// Timsort
void tim_sort(i32 *arr, i32 length);
i32 find_run(i32 *arr, i32 start, i32 length);
// Utility
void benchmark(char* option);
void pri32_i32_arr(i32 *arr, i32 length);
void reverse(i32 *arr, i32 start, i32 end);

#endif
