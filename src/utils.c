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
