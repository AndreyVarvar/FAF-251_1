#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "benchmark.h"
#include "./sorting_algorithms/sorts.h"

static inline double now_sec(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

void random_benchmark(char **options, i32 options_length, i32 arr_length, FILE *csv_out)
{
    i32 *arr = generate_random_i32_array(arr_length);

    for (i32 i = 0; i < options_length; ++i)
    {
        i32 *copy_arr = malloc(arr_length * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_length * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_length, csv_out, "Random");

        free(copy_arr);
    }

    free(arr);
}

void monotonic_benchmark(char **options, i32 options_length, i32 arr_length, i32 max_step, FILE *csv_out)
{
    i32 *arr = malloc(arr_length * sizeof *arr);
    generate_monotonic_random_steps(arr, arr_length, max_step);

    const char *mode = (max_step > 0) ? "Ascending" : "Descending";

    for (i32 i = 0; i < options_length; ++i)
    {
        i32 *copy_arr = malloc(arr_length * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_length * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_length, csv_out, mode);

        free(copy_arr);
    }

    free(arr);
}

void partially_sorted_benchmark(char **options, i32 options_length, i32 arr_length, i32 max_step, i32 max_displacement, FILE *csv_out)
{
    i32 *arr = malloc(arr_length * sizeof *arr);
    generate_monotonic_random_steps(arr, arr_length, max_step);

    // Each element moves at most max_displacement positions
    for (i32 i = 0; i < arr_length; i++)
    {
        i32 j = i + (rand() % (2 * max_displacement + 1)) - max_displacement;
        if (j < 0) j = 0;
        if (j >= arr_length) j = arr_length - 1;

        SWAP(i32, arr + i, arr + j);
    } 

    for (i32 i = 0; i < options_length; ++i)
    {
        i32 *copy_arr = malloc(arr_length * sizeof *copy_arr);
        memcpy(copy_arr, arr, arr_length * sizeof *copy_arr);

        copy_arr = benchmark(options[i], copy_arr, arr_length, csv_out, "Partially");

        free(copy_arr);
    }

    free(arr);
}

i32 *benchmark(char *option, i32 *arr, i32 length, FILE *csv_out, const char *mode)
{
    if (strcmp("kind_stalin", option) == 0 && length >= 100000)
        return arr;
    // Console output
    printf("Started %s sort (%s).\n", option, mode);
    fflush(stdout);

    // CSV log
    if (csv_out)
        fprintf(csv_out, "%s,%s,%d,", mode, option, length);

    double start = now_sec();

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
    else if (strcmp("cruel_stalin", option) == 0)
        arr = cruel_stalin_sort(arr, &length);
    else if (strcmp("kind_stalin", option) == 0)
        kind_stalin_sort(arr, length);

    double end = now_sec();

    double elapsed = end - start;

    i32 check = is_sorted(arr, length);

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

void generate_monotonic_random_steps(i32 *arr, i32 length, i32 max_step)
{
    if (length <= 0)
        return;

    i32 current = 0;
    arr[0] = current;

    if (max_step > 0)
    {
        // Ascending
        for (i32 i = 1; i < length; i++)
        {
            i32 s = 1 + rand() % max_step;
            current += s;
            arr[i] = current;
        }
    }
    else
    {
        // Descending
        max_step = -max_step;  // make positive for rand()
        for (i32 i = 1; i < length; i++)
        {
            i32 s = 1 + rand() % max_step;
            current -= s;
            arr[i] = current;
        }
    }
}

i32 is_sorted(i32 *arr, i32 length)
{
    i32 check = 1;
    for (i32 i = 1; i < length; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            check = 0;
            break;
        }
    }
    return check;
}

i32 *generate_random_i32_array(i32 length)
{
    i32 *arr = malloc(length * sizeof(i32));

    for (i32 i = 0; i < length; i++)
    {
        i32 sign = (rand() % 2) ? 1 : -1;
        arr[i] = sign * rand();
    }

    return arr;
}
