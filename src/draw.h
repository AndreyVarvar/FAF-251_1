#ifndef DRAW_H
#define DRAW_H

#include <SDL3/SDL.h>

#include "base.h"

void print_error();
void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display);
void render_texture_fit_center(SDL_Renderer *renderer, SDL_Texture *dst_texture, SDL_Texture *src_texture);
void clear_texture(SDL_Renderer *renderer, SDL_Texture *target);

#endif
