#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "base.h"
#include "misc.h"


u32 *generate_gradient_array(i32 *arr, i32 width, i32 height)
{
    u32 *color_array = calloc(width * height, sizeof(SDL_Color));
    for (i32 y = 0; y < height; y++)
    {
        for (i32 x = 0; x < width; x++)
        {
            u8 r = (u8)((double)x/ width * 255);
            u8 g = (u8)((double)(x + y)/(width * height) * 255);
            u8 b = (u8)((double)y/ height * 255);
            color_array[arr[y * width + x]] = r << 24 | g << 16 | b << 8 | 255;
        }
    }
    return color_array;
}

void render_array(SDL_Renderer *renderer, SDL_Texture *texture, i32 *indices, u32 *color_array, i32 width, i32 height)
{
    void *pixels;
    i32 pitch;
    const SDL_PixelFormatDetails *px_details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    u32 *row;
    for (i32 y = 0; y < height; y++)
    {
        row = (u32*)((u8*)pixels + y * pitch);
        for (i32 x = 0; x < width; x++)
        {
            row[x] = color_array[indices[y * width + x]];
        }
    }
    SDL_UnlockTexture(texture);
}

SDL_FRect generate_array_rect(i32 length)
{
    i32 max_w = 0, max_h = 0;
    for (i32 i = 1; i <= sqrt(length); i++)
    {
        // I know, pretty cursed
        if ((length % i == 0 && abs(max_w - max_h) > abs(length/i - i)) || (max_w == 0 && max_h == 0))
        {
            max_w = i > length/i ? i : length/i;
            max_h = i > length/i ? length/i : i;
        }
    }

    return (SDL_FRect) {.x = 0, .y = 0, .w = max_w, .h = max_h};
}
