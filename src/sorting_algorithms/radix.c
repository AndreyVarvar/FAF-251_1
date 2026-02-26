#include <stdlib.h>
#include <string.h>

#include "sorts.h"
#include "../base.h"

void radix_sort(i32 *restrict arr, i32 length)
{
    if (length <= 1)
        return;

    i32 *tmp = aligned_alloc(64, length * sizeof(i32));
    if (!tmp)
        return;

    // Flip sign bit to handle signed i32s
    for (i32 i = 0; i < length; i++)
        arr[i] ^= 0x80000000;

    i32 *in  = arr;
    i32 *out = tmp;

    const i32 RADIX = 256;
    i32 count[RADIX];

    for (i32 pass = 0; pass < 4; pass++)
    {
        memset(count, 0, sizeof(count));
        i32 shift = pass * 8;

        // Count digits
        for (i32 i = 0; i < length; i++)
            count[(in[i] >> shift) & 0xFF]++;

        // Prefix sum
        i32 sum = 0;
        for (i32 i = 0; i < RADIX; i++)
        {
            i32 t = count[i];
            count[i] = sum;
            sum += t;
        }

        // Stable scatter
        for (i32 i = 0; i < length; i++)
        {
            i32 d = (in[i] >> shift) & 0xFF;
            out[count[d]++] = in[i];
        }

        // Swap buffers
        i32 *tmp_ptr = in;
        in = out;
        out = tmp_ptr;
    }

    // If final data is in tmp, copy back once
    if (in != arr)
        memcpy(arr, in, length * sizeof(i32));

    // Restore sign bit
    for (i32 i = 0; i < length; i++)
        arr[i] ^= 0x80000000;

    free(tmp);
}
