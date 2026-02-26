#include <stdio.h>
#include <time.h>
#include "benchmark.h"
#include "utils.h"

int main(void) {
    char *options[] = {
        "selection",
        "insertion",
        "bubble",
        "shell",
        "merge",
        "heap",
        "tim",
        "quick",
        "radix",
        "cruel_stalin",
        // "kind_stalin"
    };
    int options_length = sizeof(options) / sizeof(options[0]);

    int max_step, max_displacement;
    int min_arr_length = 100; 
    int max_arr_length = 1000000;

    // Open CSV file
    FILE *csv_out = fopen("benchmark_results.csv", "w");
    if (!csv_out)
    {
        perror("Failed to open CSV file");
        return 1;
    }

    // CSV header
    fprintf(csv_out, "Mode,Sort,ArrayLength,TimeSeconds,Success\n");

    /* Randomly ordered elements */ 
    print_separator('=', 40);
    printf("Randomly ordered elements \n");
    print_separator('=', 40);
    for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    {
        printf("\n");
        print_separator('-', 20);
        printf("Length: %d\n", arr_length);
        print_separator('-', 20);
        random_benchmark(options, options_length, arr_length, time(NULL), csv_out);
    }

    /* Elements sorted in ascending order */
    print_separator('=', 40);
    printf("Elements sorted in ascending order\n");
    print_separator('=', 40);
    max_step = 10;
    for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    {
        printf("\n");
        print_separator('-', 20);
        printf("Length: %d\n", arr_length);
        print_separator('-', 20);
        monotonic_benchmark(options, options_length, arr_length, max_step, csv_out);
    }

    /* Elements sorted in descending order */
    print_separator('=', 40);
    printf("Elements sorted in descending order\n");
    print_separator('=', 40);
    max_step = -10;
    for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    {
        printf("\n");
        print_separator('-', 20);
        printf("Length: %d\n", arr_length);
        print_separator('-', 20);
        monotonic_benchmark(options, options_length, arr_length, max_step, csv_out);
    }

    /* Partially sorted array */
    print_separator('=', 40);
    printf("Partially sorted array\n");
    print_separator('=', 40);
    max_displacement = 10;
    max_step = 10;
    for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    {
        printf("\n");
        print_separator('-', 20);
        printf("Length: %d\n", arr_length);
        print_separator('-', 20);
        partially_sorted_benchmark(options, options_length, arr_length, max_step, max_displacement, csv_out);
    }

    fclose(csv_out);
    return 0;
}
