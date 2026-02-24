#ifndef UTILS_H
#define UTILS_H

#define SWAP(T, a, b) {T temp = *(a); *(a) = *(b); *(b) = temp;}
#define min(a, b) ((a) > (b) ? (b) : (a))

void print_int_arr(int *arr, int length);
void reverse(int *arr, int start, int end);
void print_separator(char c, int width);
void print_help(char *program_name);

#endif
