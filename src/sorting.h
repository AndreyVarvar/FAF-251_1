#ifndef SORTING_H
#define SORTING_H

#include "base.h"

// Sorts
void selection_sort(i32 *arr, i32 length);
void insertion_sort(i32 *arr, i32 length);
void bubble_sort(i32 *arr, i32 length);
void shell_sort(i32 *arr, i32 length);
void merge_sort(i32 *arr, i32 length);
void heap_sort(i32 *arr, i32 length);
void tim_sort(i32 *arr, i32 length);
void stalin_sort(i32 *arr, i32 length);

// Misc
void benchmark(char* option);
void print_i32_arr(i32 *arr, i32 length);

#endif
