#include "utils.h"
#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void reverse(int *arr, int start, int end)
{
    for (int i = 0; i < (end - start) / 2; i++) {
        int t = arr[start + i];
        arr[start + i] = arr[end - 1 - i];
        arr[end - 1 - i] = t;
    }
}

void print_int_arr(int *arr, int length) {
    printf("{");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);

        if (i != length-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void print_separator(char c, int width)
{
    for (int i = 0; i < width; i++)
        putchar(c);
    putchar('\n');
}

void print_help(char *program_name)
{
    printf("Usage: %s [options] source_file output_file.\n", program_name);
    printf("\t-s\tUse Selection sort.\n");
    printf("\t-i\tUse Insertion sort.\n");
    printf("\t-b\tUse Bubble sort.\n");
    printf("\t-sh\tUse Shell sort.\n");
    printf("\t-m\tUse Merge sort.\n");
    printf("\t-h\tUse Heap sort.\n");
    printf("\t-t\tUse Time sort.\n");
    printf("\t-st\tUse Stalin sort.\n");
    printf("\t-q\tUse Quick sort.\n");
    printf("\t-g\tVisualize the sorting process.\n");
    printf("\t-o\tPlace output into <file>.\n");
    printf("\t--help\tDisplay useful info.\n");
}
