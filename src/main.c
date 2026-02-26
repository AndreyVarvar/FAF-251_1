#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "visualize.h"
#include "benchmark.h"
#include "misc.h"
#include "utils.h"

i32 main(i32 argc, char *argv[])
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
        "-q", // Quick sort
        "-r", // radix sort
        "-kst", // kind Stalin sort
        "-cst", // cruel Stalin sort
    };

    i32 flags_len = sizeof(sort_flags) / sizeof(sort_flags[0]);
    u8 sorts_selected[11] = {0};
    u8 how_many_sorts = 0;

    char *output_file = NULL;
    char *input_file = NULL;
    u8 visualize = 0;

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
                if (strcmp(argv[i], "-g") == 0)
                {
                    found_flag = 1;
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
        "kind_stalin",
        "cruel_stalin",
    };

    i32 options_length = sizeof(options) / sizeof(options[0]);

    i32 min_arr_length = 100;
    i32 max_arr_length = 1000000;

    // // Open CSV file
    // FILE *csv_out = fopen("benchmark_results.csv", "w");
    // if (!csv_out)
    // {
    //     perror("Failed to open CSV file");
    //     return 1;
    // }
    //
    // // CSV header
    // fprintf(csv_out, "Mode,Sort,ArrayLength,TimeSeconds,Success\n");
    //
    // /* Randomly ordered elements */ 
    // print_separator('=', 40);
    // printf("Randomly ordered elements \n");
    // print_separator('=', 40);
    // for (i32 arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    // {
    //     printf("\n");
    //     print_separator('-', 20);
    //     printf("Length: %d\n", arr_length);
    //     print_separator('-', 20);
    //     random_benchmark(options, options_length, arr_length, csv_out);
    // }
    //
    // /* Elements sorted in ascending order */
    // print_separator('=', 40);
    // printf("Elements sorted in ascending order\n");
    // print_separator('=', 40);
    // i32 max_step = 10;
    // for (i32 arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    // {
    //     printf("\n");
    //     print_separator('-', 20);
    //     printf("Length: %d\n", arr_length);
    //     print_separator('-', 20);
    //     monotonic_benchmark(options, options_length, arr_length, max_step, csv_out);
    // }
    //
    // /* Elements sorted in descending order */
    // print_separator('=', 40);
    // printf("Elements sorted in descending order\n");
    // print_separator('=', 40);
    // max_step = -10;
    // for (i32 arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    // {
    //     printf("\n");
    //     print_separator('-', 20);
    //     printf("Length: %d\n", arr_length);
    //     print_separator('-', 20);
    //     monotonic_benchmark(options, options_length, arr_length, max_step, csv_out);
    // }
    /* Partially sorted array */
    // print_separator('=', 40);
    // printf("Partially sorted array\n");
    // print_separator('=', 40);
    // max_displacement = 10;
    // max_step = 10;
    // for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    // {
    //     printf("\n");
    //     print_separator('-', 20);
    //     printf("Length: %d\n", arr_length);
    //     print_separator('-', 20);
    //     partially_sorted_benchmark(options, options_length, arr_length, max_step, max_displacement, csv_out);
    // }
    //
    // fclose(csv_out);

    run(how_many_sorts, sorts_selected);
}
