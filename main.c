#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>


void print_int_arr(int *arr, int length);
void bubble_sort(int *arr, int length);
void shell_sort(int *arr, int length);
void insertion_sort(int *arr, int length);
void merge(int *arr, int left, int mid, int right);
void merge_sort(int *arr, int left, int right);
void heap_sort(int *arr, int n);
void heapify(int *arr, int n, int i);
void selection_sort(int *arr, int n);
void benchmark(char* option);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char** options = {
        "selection",
        "insertion",
        "bubble",
        "shell",
        "merge",
        "heap",
        //add if new sorts
    };
    for (int i = 0; i < 6; i++) //increase if new sorts
    {
        benchmark(options[i]);
    }
}

void benchmark(char* option)
{
    int size = 1000000;
    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        int sign = (rand() % 2 == 1) ? 1 : -1;
        arr[i] = (sign) * (rand() % 2000000000);
    }
    clock_t start = clock();
    if      (strcmp("bubble", option) == 0)
    {
        bubble_sort(arr, size);
    }
    else if (strcmp("shell", option) == 0)
    {
        shell_sort(arr, size);
    }
    else if (strcmp("insertion", option) == 0)
    {
        insertion_sort(arr, size);
    }
    else if (strcmp("merge", option) == 0)
    {
        merge_sort(arr, 0, size-1);
    }
    else if (strcmp("heap", option) == 0)
    {
        heap_sort(arr, size);
    }
    else if(strcmp("selection", option) == 0)
    {
        selection_sort(arr, size);
    }
    //add if new sorts
    clock_t end = clock();
    int check = 1;
    for (int i = 1; i < size; i++)
    {
        if (arr[i-1] > arr[i])
        {
            check = 0;
            break;
        }
    }
    if (check)
    {
        printf("%s successfull. CPU time: %d\n", option, end-start);
    }
    else
    {
        printf("%s unsuccessfull.\n");
    }
    free(arr);
}

void bubble_sort(int *arr, int length) {
    uint8_t sorted = 0;
    while (!sorted) {
        sorted = 1;
        for(int i = 1; i < length; i++) {
            if(arr[i-1] > arr[i]) {
                int temp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = temp;
                sorted = 0;
            }
        }
    }
}

void shell_sort(int *arr, int length) {
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void insertion_sort(int *arr, int length) {
    for (int i = 1 ; i < length - 1 ; i++) {
        int key = arr[i];
        int j = i - 1 ;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

void merge(int *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int left_arr[n1], right_arr[n2];

    for (i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        }
        else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int *arr, int left, int right) {
    if (left < right) {

        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void heap_sort(int *arr, int length)
{
    for (int i = length/2; i >= 0; i--)
    {
        heapify(arr, length, i);
    }
    for (int i = length - 1; i > 0; i--)
    {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

void heapify(int *arr, int length, int i)
{
    int max = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < length && arr[left] > arr[max])
    {
        max = left;
    }
    if (right < length && arr[right] > arr[max])
    {
        max = right;
    }
    if (max != i)
    {
        int tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, length, max);
    }
}

void selection_sort(int *arr, int n) {
	int i, j, min_idx, temp;

	for (i = 0; i < n - 1; i++) {
		// Find the index of the minimum element in the unsorted portion
		min_idx = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_idx]) {
				min_idx = j;
			}
		}

		// Swap the found minimum element with the first element of the unsorted portion
		if (min_idx != i) {
			temp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = temp;
		}
	}
}

void print_int_arr(int *arr, int length) {
    printf("{");
    for (int i = 0; i < length; i++) {
        printf("%d", arr[i]);

        if (i != length-1) {
            printf(", ");
        }
    }
    printf("}");
}
