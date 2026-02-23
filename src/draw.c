#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "base.h"
#include "draw.h"
#include "sorting.h"

void clear_texture(SDL_Renderer *renderer, SDL_Texture *target)
{
    SDL_SetRenderTarget(renderer, target);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display)
{
    SDL_SetRenderTarget(renderer, NULL);

    i32 window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    double scale_x = (double) window_width / display->w;
    double scale_y = (double) window_height / display->h;
    double min_scale = scale_x > scale_y ? scale_y : scale_x;

    u32 to_center_x = (window_width - display->w * min_scale) / 2;
    u32 to_center_y = (window_height - display->h * min_scale) / 2;

    SDL_FRect rect = {to_center_x, to_center_y, display->w * min_scale, display->h * min_scale};

    SDL_RenderTexture(renderer, display, NULL, &rect);
}

void print_error()
{
    fprintf(stderr, "%s", SDL_GetError());
}

SDL_Color *generate_gradient_array(i32 width, i32 height)
{
    SDL_Color *color_array = calloc(width * height, sizeof(SDL_Color));

    for (i32 y = 0; y < height; y++)
    {
        for (i32 x = 0; x < width; x++)
        {
            u8 r = (u8)((double)x / width * 255);
            u8 g = (u8)((double)(x + y)/(width * height) * 255);
            u8 b = (u8)((double)y / height * 255);
            color_array[y * width + x] = (SDL_Color) {r, g, b, 255};
        }
    }

    return color_array;
}

void swap_pixels(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Color color_1, SDL_Point pos_1, SDL_Color color_2, SDL_Point pos_2)
{
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, color_1.r, color_1.g, color_1.b, 255);
    SDL_RenderPoint(renderer, pos_2.x, pos_2.y);
    SDL_SetRenderDrawColor(renderer, color_2.r, color_2.g, color_2.b, 255);
    SDL_RenderPoint(renderer, pos_1.x, pos_1.y);
}

void render_array(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Color *arr, i32 width, i32 height)
{
    SDL_SetRenderTarget(renderer, texture);
    for (i32 y = 0; y < height; y++)
    {
        for (i32 x = 0; x < width; x++)
        {
            u8 r = arr[y * width + x].r;
            u8 g = arr[y * width + x].g;
            u8 b = arr[y * width + x].b;
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderPoint(renderer, x, y);
        }
    }
}
