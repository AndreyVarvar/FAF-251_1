#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <time.h>
#include "base.h"

void random_benchmark(char **options, i32 options_length, i32 arr_length, FILE *csv_out);
void monotonic_benchmark(char **options, i32 options_length, i32 arr_length, i32 max_step, FILE *csv_out);
void generate_monotonic_random_steps(i32 *arr, i32 arr_length, i32 max_step);
void partially_sorted_benchmark(char **options, i32 options_length, i32 arr_length, i32 max_step, i32 max_displacement, FILE *csv_out);
i32 *benchmark(char *option, i32 *arr, i32 length, FILE *csv_out, const char *mode);
i32 *generate_random_i32_array(i32 length);
i32 is_sorted(i32 *arr, i32 length);

#endif
