#ifndef DRAW_H
#define DRAW_H

#include <SDL3/SDL.h>

#include "base.h"

void print_error();
void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display);
void swap_pixels(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Color color_1, SDL_Point pos_1, SDL_Color color_2, SDL_Point pos_2);
void render_array(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Color *arr, i32 width, i32 height);
SDL_Color *generate_gradient_array(i32 width, i32 height);
void clear_texture(SDL_Renderer *renderer, SDL_Texture *target);

#endif
