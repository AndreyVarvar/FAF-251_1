#ifndef SORTS_H
#define SORTS_H

void selection_sort(int *arr, int length);
void insertion_sort(int *arr, int start, int end);
void bubble_sort(int *arr, int length);
void shell_sort(int *arr, int length);
void merge_sort(int *arr, int left, int right);
void heap_sort(int *arr, int length);
void quick_sort(int *arr, int low, int high);
void tim_sort(int *arr, int length);
void stalin_sort(int *arr, int n);
int *cruel_stalin_sort(int *arr, int *length);

#endif