#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "../include/benchmark.h"
#include "../include/utils.h"
#include "base.h"

#include "../include/sorting.h"
#include "visualize.h"
#include "swap_list.h"
#include "record.h"
#include "draw.h"

void print_help(char *program_name);

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

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // more concise than what was before (Sorry Max)
    char *sort_flags[] =
    {
        "-s", // Selection sort
        "-i", // Insertion sort
        "-b", // Bubble sort
        "-sh", // Shell sort
        "-m", // Merge sort
        "-h", // Heap sort
        "-t", // Tim sort
        "-st", // Stalin sort
        "-q", // Quick sort
    };

    i32 flags_len = sizeof(sort_flags) / sizeof(sort_flags[0]);
    u8 sorts_selected[flags_len] = {};
    u8 how_many_sorts = 0;

    for (u8 i=0;i<flags_len;i++)
    {
        sorts_selected[i] = 0;
    }

    char *output_file = "output.txt";
    char *input_file = NULL;

    // Goofy ahh argument parsing (Sorry Cristi)
    // Probably should move this to a function... (Aiden)
    if (argc > 1) {
        for (u8 i=1;i<argc;i++)
        {
            if (strcmp(argv[i], "--help") == 0)
            {
                print_help(argv[0]);
                return 0;
            } else
            {
                u8 found_flag = 0;
                for (u8 j=0;j<flags_len;j++)
                {
                    if (strcmp(argv[i], sort_flags[j]) == 0)
                    {
                        sorts_selected[how_many_sorts] = j;
                        found_flag = 1;
                        how_many_sorts++;
                        break;
                    }
                }
                if (strcmp(argv[i], "-o") == 0)
                {
                    if (i + 1 < argc)
                    {
                        output_file = argv[i + 1];
                        found_flag = 1;
                        i++;
                    } else
                    {
                        printf("No output file selected.\n");
                        return 0;
                    }
                }
                if (!found_flag)
                {
                    input_file = argv[i];
                }
            }
        }
    } else
    {
        print_help(argv[0]);
        return 0;
    }

    if (!input_file)
    {
        printf("No input file selected.\n");
        return 0;
    }

    if (!how_many_sorts)
    {
        printf("No sorts selected.\n");
        return 0;
    }
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
