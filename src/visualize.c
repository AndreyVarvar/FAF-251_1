#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

#include "base.h"
#include "visualize.h"
#include "sort_by_step.h"
#include "draw.h"
#include "misc.h"
#include "utils.h"

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
    SortData sort_data = {.length = length};
    i32 *indices = malloc(length * sizeof(i32));

    for (i32 i = 0; i < length; i++)
    {
        indices[i] = i;
    }
    i32 *alt_indices = malloc(length * sizeof(i32));

    for (i32 i = 0; i < length; i++)
    {
        alt_indices[i] = i;
    }

    while (!radix_sort_step(arr, alt_indices, &sort_data)) {}


    SDL_Color *color_array = generate_gradient_array(alt_indices, array_width, array_height);

    free(alt_indices);

    u64 current_time = SDL_GetPerformanceCounter(), previous_time;
    f64 dt_accumulator = 0, dt = (double)1/120;

    u8 done = 0;
    while (!done)
    {
        clear_texture(renderer, NULL);
        clear_texture(renderer, display);

        previous_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        dt_accumulator += (double)(current_time - previous_time)/SDL_GetPerformanceFrequency();

        while (dt_accumulator > dt)
        {
            dt_accumulator = 0;
            radix_sort_step(arr, indices, &sort_data);
            render_array(renderer, array_texture, indices, color_array, array_width, array_height);
        }

        SDL_Event event;
        while (SDL_PollEvent(&event) == 1)
        {
            if (event.type == SDL_EVENT_QUIT) done = 1;
        }

        SDL_SetRenderTarget(renderer, display);
        SDL_RenderTexture(renderer, array_texture, &array_rect, &array_rect);
        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    free(indices);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
