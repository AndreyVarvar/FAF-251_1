#ifndef UTILS_H
#define UTILS_H

#include "base.h"

#define SWAP(T, a, b) {T temp = *(a); *(a) = *(b); *(b) = temp;}
#define min(a, b) ((a) > (b) ? (b) : (a))

void print_i32_arr(i32 *arr, i32 length);
void reverse(i32 *arr, i32 start, i32 end);
void print_separator(char c, i32 width);
void print_help(char *program_name);

#endif
