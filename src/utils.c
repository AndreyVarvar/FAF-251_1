#include <stdio.h>

#include "base.h"
#include "utils.h"

void reverse(i32 *arr, i32 start, i32 end)
{
    for (i32 i = 0; i < (end - start) / 2; i++) {
        SWAP(i32, arr + start + i, arr + end - 1 - i);
    }
}

void print_i32_arr(i32 *arr, i32 length) {
    printf("{");
    for (i32 i = 0; i < length; i++) {
        printf("%d", arr[i]);

        if (i != length-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void print_separator(char c, i32 width)
{
    for (i32 i = 0; i < width; i++)
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
    printf("\t-q\tUse Quick sort.\n");
    printf("\t-r\tUse Radix sort.\n");
    printf("\t-st\tUse kind Stalin sort.\n");
    printf("\t-st\tUse crue Stalin sort.\n");
    printf("\t-g\tVisualize the sorting process.\n");
    printf("\t-o\tPlace output into <file>.\n");
    printf("\t--help\tDisplay useful info.\n");
}
