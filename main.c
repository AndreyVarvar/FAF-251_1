#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void print_int_array(int length, int array[length]);
void bubble_sort(int length, int array[length]);


int main(int argc, char *argv[]) {
    srand(time(NULL));

    int len = 50;
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
    printf("\n");

    bubble_sort(len, sort_me);
    print_int_array(len, sort_me);
    printf("\n");
}


void bubble_sort(int length, int array[length]) {
    uint8_t sorted = 0;
    while (!sorted) {
        sorted = 1;
        for(int i = 1; i < length; i++) {
            if(array[i-1] > array[i]) {
                int temp = array[i];
                array[i] = array[i-1];
                array[i-1] = temp;
                sorted = 0;
            }
        }
    }
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
