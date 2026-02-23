#include <time.h>
#include "benchmark.h"

int main(int argc, char *argv[]) {
    char *options[] = {
        "selection\0",
        "insertion\0",
        "bubble\0",
        "shell\0",
        "merge\0",
        "heap\0",
        "tim\0",
        "stalin\0",
        "quick\0"
        //add if new sorts
    };
    int options_len = sizeof(options) / sizeof(options[0]);
    int arr_size = 10000;
    random_benchmark(options, options_len, arr_size, time(NULL));
}












