#include <stdlib.h>
#include "sorts.h"
#include "utils.h"


static int find_run(int* arr, int start, int length)
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

static void merge(int *arr, int *tmp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    for (int x = left; x <= right; x++)
    {
        tmp[x] = arr[x];
    }

    while (i <= mid && j <= right) {
        if (tmp[i] <= tmp[j]) {
            arr[k++] = tmp[i++];
        }
        else {
            arr[k++] = tmp[j++];
        }
    }

    while (i <= mid) {
        arr[k++] = tmp[i++];
    }
}

void tim_sort(int *arr, int length)
{
    int min_run = 32;
    int *tmp = malloc(length * sizeof(int));
    int runs[128][2];
    int runs_len = 0;

    int i = 0;
    while (i < length)
    {
        int run_end = find_run(arr, i, length);
        int run_len = run_end - i;
        if (run_len < min_run)
        {
            int end = (i + min_run < length) ? i + min_run : length;
            insertion_sort(arr, i, end - 1);
            run_end = end;
        }
        runs_len++;
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
                merge(arr, tmp, l1, r1 - 1, r2 - 1);
                runs_len--;
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
        merge(arr, tmp, l1, r1 - 1, r2 - 1);
        runs_len--;
        runs[runs_len - 1][0] = l1;
        runs[runs_len - 1][1] = r2;
    }
    free(tmp);
}