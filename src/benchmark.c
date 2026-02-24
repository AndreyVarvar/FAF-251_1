#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "benchmark.h"
#include "sorts.h"
#include "utils.h"

void random_benchmark(char **options, int options_length, int arr_length, time_t seed, FILE *csv_out)
{
    srand(seed);

    int *arr = malloc(arr_length * sizeof *arr);

    for (int i = 0; i < arr_length; i++)
    {
        int sign = (rand() % 2) ? 1 : -1;
        arr[i] = sign * rand();
    }

    for (int i = 0; i < options_length; ++i)
    {
        int *copy_arr = malloc(arr_length * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_length * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_length, csv_out, "Random");

        free(copy_arr);
    }

    free(arr);
}

void monotonic_benchmark(char **options, int options_length, int arr_length, int max_step, FILE *csv_out)
{
    int *arr = malloc(arr_length * sizeof *arr);
    generate_monotonic_random_steps(arr, arr_length, max_step);

    const char *mode = (max_step > 0) ? "Ascending" : "Descending";

    for (int i = 0; i < options_length; ++i)
    {
        int *copy_arr = malloc(arr_length * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_length * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_length, csv_out, mode);

        free(copy_arr);
    }

    free(arr);
}

int *benchmark(char *option, int *arr, int length, FILE *csv_out, const char *mode)
{
    // Console output
    printf("Started %s sort (%s).\n", option, mode);
    fflush(stdout);

    // CSV log
    if (csv_out)
        fprintf(csv_out, "%s,%s,%d,", mode, option, length);

    clock_t start = clock();

    if (strcmp("selection", option) == 0)
        selection_sort(arr, length);
    else if (strcmp("insertion", option) == 0)
        insertion_sort(arr, length);
    else if (strcmp("bubble", option) == 0)
        bubble_sort(arr, length);
    else if (strcmp("shell", option) == 0)
        shell_sort(arr, length);
    else if (strcmp("merge", option) == 0)
        merge_sort(arr, length);
    else if (strcmp("heap", option) == 0)
        heap_sort(arr, length);
    else if (strcmp("tim", option) == 0)
        tim_sort(arr, length);
    else if (strcmp("quick", option) == 0)
        quick_sort(arr, length);
    else if (strcmp("radix", option) == 0)
        radix_sort(arr, length);
    else if (strcmp("stalin", option) == 0)
        arr = cruel_stalin_sort(arr, &length);

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    int check = 1;
    for (int i = 1; i < length; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            check = 0;
            break;
        }
    }

    // Console output
    printf("%s sort %s.\nTime: %lf\n\n",
           option,
           check ? "successful" : "unsuccessful",
           elapsed);

    // CSV output
    if (csv_out)
        fprintf(csv_out, "%lf,%d\n", elapsed, check);

    return arr;
}

void generate_monotonic_random_steps(int *arr, int length, int max_step)
{
    if (length <= 0)
        return;

    int current = 0;
    arr[0] = current;

    if (max_step > 0)
    {
        // Ascending
        for (int i = 1; i < length; i++)
        {
            int s = 1 + rand() % max_step;
            current += s;
            arr[i] = current;
        }
    }
    else
    {
        // Descending
        max_step = -max_step;  // make positive for rand()
        for (int i = 1; i < length; i++)
        {
            int s = 1 + rand() % max_step;
            current -= s;
            arr[i] = current;
        }
    }
}