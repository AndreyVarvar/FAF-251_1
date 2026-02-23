#include <math.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "visualize.h"
#include "swap_list.h"
#include "record.h"
#include "sorting.h"
#include "draw.h"

SDL_FRect generate_array_rect(i32 length);

void run(i32 *arr, i32 length)
{

    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        print_error();
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Sorting Visualization", 1000, 1000, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        print_error();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == NULL)
    {
        print_error();
        return;
    }


    SDL_FRect array_rect = generate_array_rect(length);
    i32 array_width = array_rect.w;
    i32 array_height = array_rect.h;

    SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, array_width, array_height);
    SDL_SetTextureScaleMode(display, SDL_SCALEMODE_NEAREST);

    SDL_Texture *array_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, array_width, array_height);
    SDL_Color *color_array = generate_gradient_array(array_width, array_height);
    render_array(renderer, array_texture, color_array, array_width, array_height);

    SwapNode *start = swap_list_init(0, 0);
    SwapNode *alt_start = start;
    SwapNode *end = record_selection_sort(arr, length, start);

    u64 current_time = SDL_GetPerformanceCounter(), previous_time;
    f64 dt_accumulator = 0, dt = (double)1/120;

    i32 i, j;
    while (end)
    {
        i = end->i;
        j = end->j;

        swap_pixels(renderer, array_texture, color_array[i], (SDL_Point) {i%array_width,i/array_width}, color_array[j], (SDL_Point) {j%array_width,j/array_width});
        SWAP(SDL_Color, color_array + i, color_array + j);

        end = end->prev;
    }

    u8 done = 0;
    while (!done)
    {
        previous_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        dt_accumulator += (double)(current_time - previous_time)/SDL_GetPerformanceFrequency();

        if (dt_accumulator > dt && start)
        {
            i = start->i;
            j = start->j;

            swap_pixels(renderer, array_texture, color_array[i], (SDL_Point) {i%array_width,i/array_width}, color_array[j], (SDL_Point) {j%array_width,j/array_width});
            SWAP(SDL_Color, color_array + i, color_array + j);

            start = start->next;

            dt_accumulator = 0;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event) == 1)
        {
            if (event.type == SDL_EVENT_QUIT) done = 1;
        }

        clear_texture(renderer, NULL);
        clear_texture(renderer, display);
        SDL_RenderTexture(renderer, array_texture, &array_rect, &array_rect);
        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    swap_list_destroy(alt_start);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_FRect generate_array_rect(i32 length)
{
    i32 max_w = 0, max_h = 0;
    for (i32 i = 1; i <= sqrt(length); i++)
    {
        // I know pretty cursed
        if ((length % i == 0 && abs(max_w - max_h) > abs(length/i - i)) || (max_w == 0 && max_h == 0))
        {
            max_w = i > length/i ? i : length/i;
            max_h = i > length/i ? length/i : i;
        }
    }

    return (SDL_FRect) {.x = 0, .y = 0, .w = max_w, .h = max_h};
}

