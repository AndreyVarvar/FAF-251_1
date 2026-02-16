#ifndef SORTING_H
#define SORTING_H

#include "platform.h"

void selection_sort(int *arr, int length);
void insertion_sort(int *arr, int start, int end);
void bubble_sort(int *arr, int length);
void shell_sort(int *arr, int length);
// Merge sort
void merge_sort(int *arr, int left, int right);
void merge_sort_rec(int *arr, int *tmp, int left, int right);
void merge(int *arr, int *tmp, int left, int mid, int right);
// Heap sort
void heap_sort(int *arr, int lenght);
void heapify(int *arr, int length, int current);
// Timsort
void tim_sort(int *arr, int length);
int find_run(int *arr, int start, int length);
// Utility
void benchmark(char* option);
void print_int_arr(int *arr, int length);
void reverse(int *arr, int start, int end);

#endif
