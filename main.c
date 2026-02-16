#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

void selection_sort(int *arr, int length);
void insertion_sort(int *arr, int length);
void bubble_sort(int *arr, int length);
void shell_sort(int *arr, int length);
// Merge sort
void merge_sort(int *arr, int left, int right);
void merge(int *arr, int left, int mid, int right);
// Heap sort
void heap_sort(int *arr, int lenght);
void heapify(int *arr, int length, int current);
// Timsort
void tim_sort(int *arr, int length);
int find_run(int *arr, int start, int length);
void insert_for_tim(int *arr, int left, int right);
// Utility
void benchmark(char* option);
void print_int_arr(int *arr, int length);
void reverse(int *arr, int start, int end);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char *options[] = {
        "selection\0",
        "insertion\0",
        "bubble\0",
        "shell\0",
        "merge\0",
        "heap\0",
        "tim\0",
        //add if new sorts
    };
    int options_len = sizeof(options) / sizeof(options[0]);
    for (int i = 0; i < options_len; i++) 
    {
        benchmark(options[i]);
    }
}

void benchmark(char* option)
{
    printf("Started %s sort.\n", option);
    int size = 100000;
    int *arr = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        int sign = (rand() % 2 == 1) ? 1 : -1;
        arr[i] = (sign) * rand();
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
    else if(strcmp("tim", option) == 0)
    {
        tim_sort(arr, size);
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
        printf("%s sort successfull. CPU time: %d\n", option, end-start);
    }
    else
    {
        printf("%s sort unsuccessfull.\n", option);
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
    for (int i = 1 ; i < length; i++) {
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
    printf("}\n");
}

int find_run(int* arr, int start, int length)
{
    int end = start + 1;
    if (end == length)
    {
        return end;
    }
    if (arr[end] < arr[start])
    {
        while (end < length && arr[end] < arr[end-1])
        {
            end++;
        }
        reverse(arr, start, end);
    }
    else
    {
        while (end < length && arr[end] >= arr[end-1])
        {
            end++;
        }
    }
    return end;
}

void insert_for_tim(int *arr, int start, int end)
{
    for (int i = start + 1 ; i <= end; i++) 
    {
        int key = arr[i];
        int j = i - 1 ;
        while (j >= start && arr[j] > key) 
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

void tim_sort(int *arr, int length)
{
    int min_run = 32;
    int **runs = NULL;
    int runs_len = 0;

    int i = 0;
    while (i < length)
    {
        int run_end = find_run(arr, i, length);
        int run_len = run_end - i;
        if (run_len < min_run)
        {
            int end = (i + min_run < length) ? i + min_run : length;
            insert_for_tim(arr, i, end - 1);
            run_end = end;
        }
        runs = realloc(runs, ++runs_len * sizeof(int*));
        runs[runs_len-1] = malloc(2 * sizeof(int));
        runs[runs_len-1][0] = i;
        runs[runs_len-1][1] = run_end;
        i = run_end;

        while (runs_len > 1)
        {
            int l1 = runs[runs_len - 2][0];
            int r1 = runs[runs_len - 2][1];
            int l2 = runs[runs_len - 1][0];
            int r2 = runs[runs_len - 1][1];

            int len1 = r1 - l1;
            int len2 = r2 - l2;

            if (len1 <= len2)
            {
                merge(arr, l1, r1 - 1, r2 - 1);
                runs = realloc(runs, (--runs_len) * sizeof(int*));
                runs[runs_len - 1][0] = l1;
                runs[runs_len - 1][1] = r2;
            }
            else break;
        }
    }
    while (runs_len > 1)
    {
        int l1 = runs[runs_len - 2][0];
        int r1 = runs[runs_len - 2][1];
        int l2 = runs[runs_len - 1][0];
        int r2 = runs[runs_len - 1][1];
        merge(arr, l1, r1 - 1, r2 - 1);
        runs = realloc(runs, (--runs_len) * sizeof(int*));
        runs[runs_len - 1][0] = l1;
        runs[runs_len - 1][1] = r2;
    }
}

void reverse(int *arr, int start, int end)
{
    for (int i = 0; i < (start + end)/2 - start; i++)
    {
        int tmp = arr[start + i];
        arr[start + i] = arr[end - i];
        arr[end - i] = tmp;
    }
}