#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void radix_sort(int *restrict arr, int length)
{
    if (length <= 1)
        return;

    int *tmp = aligned_alloc(64, length * sizeof(int));
    if (!tmp)
        return;

    // Flip sign bit to handle signed ints
    for (int i = 0; i < length; i++)
        arr[i] ^= 0x80000000;

    int *in  = arr;
    int *out = tmp;

    const int RADIX = 256;
    int count[RADIX];

    for (int pass = 0; pass < 4; pass++)
    {
        memset(count, 0, sizeof(count));
        int shift = pass * 8;

        // Count digits
        for (int i = 0; i < n; i++)
            count[(in[i] >> shift) & 0xFF]++;

        // Prefix sum
        int sum = 0;
        for (int i = 0; i < RADIX; i++)
        {
            int t = count[i];
            count[i] = sum;
            sum += t;
        }

        // Stable scatter
        for (int i = 0; i < n; i++)
        {
            int d = (in[i] >> shift) & 0xFF;
            out[count[d]++] = in[i];
        }

        // Swap buffers
        int *tmp_ptr = in;
        in = out;
        out = tmp_ptr;
    }

    // If final data is in tmp, copy back once
    if (in != arr)
        memcpy(arr, in, length * sizeof(int));

    // Restore sign bit
    for (int i = 0; i < length; i++)
        arr[i] ^= 0x80000000;

    free(tmp);
}