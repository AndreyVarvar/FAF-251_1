#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

void random_benchmark(char **options, int options_len, int arr_size, time_t seed);
int *benchmark(char *option, int *arr, int size);

#endif