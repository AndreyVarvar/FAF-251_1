#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

void random_benchmark(char **options, int options_length, int arr_length, time_t seed, FILE *csv_out);
void monotonic_benchmark(char **options, int options_length, int arr_length, int max_step, FILE *csv_out);
void partially_sorted_benchmark(char **options, int options_length, int arr_length, int max_step, int max_displacement, FILE *csv_out);
void generate_monotonic_random_steps(int *arr, int arr_length, int max_step);
int *benchmark(char *option, int *arr, int length, FILE *csv_out, const char *mode);

#endif