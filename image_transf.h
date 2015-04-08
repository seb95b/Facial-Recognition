#ifndef IMAGE_TRANSF_H
#define IMAGE_TRANSF_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface* Greyscale(SDL_Surface* img);

void cum_hist(SDL_Surface* img, long* cum);

#endif
