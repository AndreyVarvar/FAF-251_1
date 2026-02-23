#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "base.h"
#include "misc.h"

void print_help(char *program_name)
{
    printf("Usage: %s [options] source_file output_file.\n", program_name);
    printf("\t-s\tUse Selection sort.\n");
    printf("\t-i\tUse Insertion sort.\n");
    printf("\t-b\tUse Bubble sort.\n");
    printf("\t-sh\tUse Shell sort.\n");
    printf("\t-m\tUse Merge sort.\n");
    printf("\t-h\tUse Heap sort.\n");
    printf("\t-t\tUse Time sort.\n");
    printf("\t-st\tUse Stalin sort.\n");
    printf("\t-q\tUse Quick sort.\n");
    printf("\t-g\tVisualize the sorting process.\n");
    printf("\t-o\tPlace output into <file>.\n");
    printf("\t--help\tDisplay useful info.\n");
}

SDL_Color *generate_gradient_array(i32 *arr, i32 width, i32 height)
{
    SDL_Color *color_array = calloc(width * height, sizeof(SDL_Color));
    for (i32 y = 0; y < height; y++)
    {
        for (i32 x = 0; x < width; x++)
        {
            u8 r = (u8)((double)x/ width * 255);
            u8 g = (u8)((double)(x + y)/(width * height) * 255);
            u8 b = (u8)((double)y/ height * 255);
            color_array[arr[y * width + x]] = (SDL_Color) {r, g, b, 255};
        }
    }
    return color_array;
}

void render_array(SDL_Renderer *renderer, SDL_Texture *texture, i32 *indices, SDL_Color *color_array, i32 width, i32 height)
{
    SDL_SetRenderTarget(renderer, texture);
    for (i32 i = 0; i < width * height; i++)
    {
        SDL_SetRenderDrawColor(renderer, color_array[indices[i]].r, color_array[indices[i]].g, color_array[indices[i]].b, 255);
        SDL_RenderPoint(renderer, i%width, i/width);
    }
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
