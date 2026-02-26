#include "sorts.h"
#include "../base.h"

void shell_sort(i32 *arr, i32 length) {
    for (i32 gap = length / 2; gap > 0; gap /= 2) {
        for (i32 i = gap; i < length; i++) {
            i32 temp = arr[i];
            i32 j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
