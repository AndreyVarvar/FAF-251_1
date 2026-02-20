#include <SDL3/SDL_render.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

#include "visualize.h"
#include "platform.h"

void print_error();
void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display);
void render_array(SDL_Renderer *renderer, SDL_Texture *display, SDL_Texture *texture, int *array, int length);

void run(int *arr, int length) {
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        print_error();
        return;
    }

    SDL_Window *window = SDL_CreateWindow("Sorting Visualization", 1000, 1000, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        print_error();
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == NULL) {
        print_error();
        return;
    }

    SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sqrt(length), sqrt(length));
    SDL_Texture *array_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sqrt(length), sqrt(length));

    u8 done = 0;
    SDL_FRect rect = {.w = sqrt(length), .h = sqrt(length)};
    while (!done) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Event event;
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_EVENT_QUIT) done = 1;
        }

        render_array(renderer, display, array_texture, arr, length);
        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display) {
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

void print_error() {
    fprintf(stderr, "%s", SDL_GetError());
}

void render_array(SDL_Renderer *renderer, SDL_Texture *display, SDL_Texture *texture, int *array, int length) {
    SDL_SetRenderTarget(renderer, texture);
    for (int y=0;y<sqrt(length);y++) {
        for (int x=0;x<sqrt(length);x++) {
            u8 r = (u8)((double)x / sqrt(length) * 255);
            u8 g = (u8)((double)(x + y)/length * 255);
            u8 b = (u8)((double)y / sqrt(length) * 255);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderPoint(renderer, x, y);
        }
    }
    SDL_SetRenderTarget(renderer, display);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
}
