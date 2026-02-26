#ifndef MISC_H
#define MISC_H

#include <SDL3/SDL.h>

#include "base.h"

void print_help(char *program_name);
u32 *generate_gradient_array(i32 *arr, i32 width, i32 height);
void render_array(SDL_Renderer *renderer, SDL_Texture *texture, i32 *indices, u32 *color_array, i32 width, i32 height);
SDL_FRect generate_array_rect(i32 length);

#endif
