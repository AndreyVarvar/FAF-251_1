#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "utils.h"
#include "visualize.h"
#include "sort_by_step.h"
#include "draw.h"
#include "misc.h"
#include "benchmark.h"

static i32 *generate_partialy_sorted_i32_array(i32 length);
static i32 *generate_random_descending_i32_array(i32 length);
static i32 *generate_random_ascending_i32_array(i32 length);

typedef i32 *(*random_array_generator)(i32 length);

void run(i32 how_many_sorts, i32 (*sorts_selected)[2])
{
    random_array_generator random_array_generators[4] = {
        generate_random_i32_array,
        generate_random_ascending_i32_array,
        generate_random_descending_i32_array,
        generate_partialy_sorted_i32_array
    };

    step_sort_function sorts[11] = {
        selection_sort_step,
        insertion_sort_step,
        bubble_sort_step,
        shell_sort_step,
        merge_sort_step,
        heap_sort_step,
        tim_sort_step,
        quick_sort_step,
        radix_sort_step,
        kind_stalin_sort_step
    };

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

    for (i32 x = 0; x < 4; x++)
    {
        for (i32 i = 0; i < how_many_sorts; i++)
        {
            i32 length = sorts_selected[i][1];
            SDL_FRect array_rect = generate_array_rect(length);
            i32 array_width = array_rect.w;
            i32 array_height = array_rect.h;

            SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, array_width, array_height);
            SDL_SetTextureScaleMode(display, SDL_SCALEMODE_NEAREST);

            i32 *arr = random_array_generators[x](length);
            SDL_Texture *array_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, array_width, array_height);
            SortData sort_data = {.length = length};

            i32 *indices = malloc(length * sizeof(i32));
            for (i32 j = 0; j < length; j++) indices[j] = j;

            i32 *alt_indices = malloc(length * sizeof(i32));
            for (i32 j = 0; j < length; j++) alt_indices[j] = j;

            while (!sorts[sorts_selected[i][0]](arr, alt_indices, &sort_data)) {}

            u32 *color_array = generate_gradient_array(alt_indices, array_width, array_height);

            free(alt_indices);

            u64 current_time = SDL_GetPerformanceCounter(), previous_time;
            f64 dt_accumulator = 0, dt = (double)1/20;

            u8 done = 0;
            while (!done)
            {
                clear_texture(renderer, NULL);
                clear_texture(renderer, display);

                previous_time = current_time;
                current_time = SDL_GetPerformanceCounter();
                dt_accumulator += (double)(current_time - previous_time)/SDL_GetPerformanceFrequency();

                if (dt_accumulator > dt && !is_sorted_by(arr, indices, length))
                {
                    sorts[sorts_selected[i][0]](arr, indices, &sort_data);
                    dt_accumulator = 0;
                }

                SDL_Event event;
                while (SDL_PollEvent(&event) == 1)
                {
                    if (event.type == SDL_EVENT_QUIT) done = 1;
                }

                render_array(renderer, array_texture, indices, color_array, array_width, array_height);
                SDL_SetRenderTarget(renderer, display);
                SDL_RenderTexture(renderer, array_texture, NULL, NULL);
                render_display(renderer, window, display);
                SDL_RenderPresent(renderer);
            }
            free(indices);
            free(arr);
            SDL_DestroyTexture(display);
            SDL_DestroyTexture(array_texture);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static i32 *generate_partialy_sorted_i32_array(i32 length)
{
    i32 *arr = malloc(length * sizeof *arr);
    generate_monotonic_random_steps(arr, length, 10);

    // Each element moves at most max_displacement positions
    for (i32 i = 0; i < length; i++)
    {
        i32 j = i + (rand() % (2 * 10 + 1)) - 10;
        if (j < 0) j = 0;
        if (j >= length) j = length - 1;

        SWAP(i32, arr + i, arr + j);
    }
    return arr;
}

static i32 *generate_random_ascending_i32_array(i32 length)
{
    i32 *arr = malloc(length * sizeof(i32));
    i32 current = 0;
    arr[0] = current;

    for (i32 i = 1; i < length; i++)
    {
        i32 s = 1 + rand() % 10;
        current += s;
        arr[i] = current;
    }

    return arr;
}

static i32 *generate_random_descending_i32_array(i32 length)
{
    i32 *arr = malloc(length * sizeof(i32));
    i32 current = 0;
    arr[0] = current;

    for (i32 i = 1; i < length; i++)
    {
        i32 s = 1 + rand() % 10;
        current -= s;
        arr[i] = current;
    }
    return arr;
}
