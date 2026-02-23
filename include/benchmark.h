#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

void random_benchmark(char **options, int options_length, int arr_length, time_t seed);
void monotonic_benchmark(char **options, int options_length, int arr_length, int max_step);
void generate_monotonic_random_steps(int *arr, int arr_length, int max_step);
int *benchmark(char *option, int *arr, int length);

#endif