#ifndef SDL_STUFF_H
#define SDL_STUFF_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void wait_for_keypressed(void);

void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

#endif
