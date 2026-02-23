#include <time.h>
#include <stdio.h>
#include "benchmark.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    char *options[] = {
        // "selection\0",
        // "insertion\0",
        // "bubble\0",
        "shell\0",
        "merge\0",
        "heap\0",
        "tim\0",
        "stalin\0",
        "quick\0"
        //add if new sorts
    };
    int options_length = sizeof(options) / sizeof(options[0]);
    
    // array length from 100 to 10000000
    int min_arr_length = 100; 
    int max_arr_length = 10000000;

    print_separator('=', 40);
    printf("Randomly ordered elements\n");
    print_separator('=', 40);
    // printf("\n");
    for (int arr_length = min_arr_length; arr_length <= max_arr_length; arr_length *= 10)
    {
        printf("\n");
        print_separator('-', 20);
        printf("Length: %d\n", arr_length);
        print_separator('-', 20);
        random_benchmark(options, options_length, arr_length, time(NULL));
        // print_separator('-', 20);
    }

}












