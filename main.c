#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void print_int_array(int length, int array[length]);


int main(int argc, char *argv[]) {
    srand(time(NULL));

    int len = 1000;
    int magnitude = 1000; // -magnitude <= rand() <= +magnitude
    int sort_me[len];

    for (int i = 0; i < len; i++) {
        int negative = rand() % 2;
        sort_me[i] = (rand() % (2*magnitude));
        if (negative) {
            sort_me[i] *= -1;
        }
    }

    print_int_array(len, sort_me);
}


void print_int_array(int length, int array[length]) {
    printf("{");
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);

        if (i != length-1) {
            printf(", ");
        }
    }
    printf("}");
}
