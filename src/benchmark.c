#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"
#include "sorts.h"

void random_benchmark(char **options, int options_len, int arr_size, time_t seed)
{
    srand(seed);

    int *arr = malloc(arr_size * sizeof *arr);

    for (int i = 0; i < arr_size; i++)
    {
        int sign = (rand() % 2) ? 1 : -1;
        arr[i] = sign * rand();
    }

    for (int i = 0; i < options_len; ++i)
    {
        int *copy_arr = malloc(arr_size * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_size * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_size);

        free(copy_arr);
    }

    free(arr);
}

int *benchmark(char *option, int *arr, int size)
{
    printf("Started %s sort.\n", option);

    clock_t start = clock();

    if (strcmp("selection", option) == 0)
        selection_sort(arr, size);
    else if (strcmp("insertion", option) == 0)
        insertion_sort(arr, 0, size - 1);
    else if (strcmp("bubble", option) == 0)
        bubble_sort(arr, size);
    else if (strcmp("shell", option) == 0)
        shell_sort(arr, size);
    else if (strcmp("merge", option) == 0)
        merge_sort(arr, 0, size - 1);
    else if (strcmp("heap", option) == 0)
        heap_sort(arr, size);
    else if (strcmp("tim", option) == 0)
        tim_sort(arr, size);
    else if (strcmp("stalin", option) == 0)
        arr = cruel_stalin_sort(arr, &size);
    else if (strcmp("quick", option) == 0)
        quick_sort(arr, 0, size - 1);

    clock_t end = clock();

    int check = 1;
    for (int i = 1; i < size; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            check = 0;
            break;
        }
    }

    printf("%s sort %s.\nTime: %lf\n\n",
           option,
           check ? "successful" : "unsuccessful",
           (double)(end - start) / CLOCKS_PER_SEC);

    return arr;
}