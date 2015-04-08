#include <stdio.h>
#include "image_transf.h"
#include "pixel_operations.h"

SDL_Surface* Greyscale(SDL_Surface* img) {
	
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			Uint32 pixel = getpixel(img, i, j);
			Uint8 r;
			Uint8 g;
			Uint8 b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			int gris = ((3 * r) / 10.0 + (59 * g) / 100.0 + (11 * b) / 100.0);
			pixel = SDL_MapRGB(img->format, gris, gris, gris);
			putpixel(img, i, j, pixel);
		}
	}
	return img;
}
