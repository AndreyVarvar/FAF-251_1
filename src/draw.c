#include <stdio.h>

#include "base.h"
#include "draw.h"

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
