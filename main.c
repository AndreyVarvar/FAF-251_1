#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


void print_int_array(int length, int array[length]);
void bubble_sort(int length, int array[length]);
void shell_sort(int length, int array[length]);
void insertion_sort(int length, int array[length]);
void merge(int array[], int left, int mid, int right);
void merge_sort(int array[], int left, int right);
void heap_sort(int arr[], int n);
void heapify(int arr[], int n, int i);
void selection_sort(int *arr, int n);


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

    shell_sort(len, sort_me);
    print_int_array(len, sort_me);
    printf("\n");
    
    insertion_sort(len, sort_me);
    print_int_array(len, sort_me);
    printf("\n");

    merge_sort(sort_me, 0, len - 1);
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

void shell_sort(int length, int array[length]) {
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; i++) {
            int temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
}

void insertion_sort(int length, int array[length]) {
    for (int i = 1 ; i < length - 1 ; i++) {
        int key = array[i];
        int j = i - 1 ;
        while (j >= 0 && array[j] > key) {
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = key;
    }
}

void merge(int array[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int left_arr[n1], right_arr[n2];

    for (i = 0; i < n1; i++)
        left_arr[i] = array[left + i];
    for (j = 0; j < n2; j++)
        right_arr[j] = array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            array[k] = left_arr[i];
            i++;
        }
        else {
            array[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right_arr[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int left, int right) {
    if (left < right) {
      
        int mid = left + (right - left) / 2;

        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

void heap_sort(int arr[], int n)
{
    for (int i = n/2; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i)
{
    int max = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < n && arr[left] > arr[max])
    {
        max = left;
    }
    if (right < n && arr[right] > arr[max])
    {
        max = right;
    }
    if (max != i)
    {
        int tmp = arr[i];
        arr[i] = arr[max];
        arr[max] = tmp;
        heapify(arr, n, max);
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
