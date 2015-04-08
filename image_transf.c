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

void cum_hist(SDL_Surface* img, long* cum) {
	
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			Uint32 pixel = getpixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			cum[r] += 1;
		}
	}
	
	for(int i = 1; i < 256; i++) {
		cum[i] += cum[i-1]; 
	}

	/*long min = cum[0];
	for(int i = 0; i < 256; i++) 
		cum[i] -= min;

	long max = cum[255];
	for(int i = 0; i < 256; i++) 
		cum[i] = cum[i]/max;
	
	for(int i = 0; i < 256; i++) 
		cum[i] = 255*cum[i];*/
}

SDL_Surface* norm(SDL_Surface* img) {
	char max = 0, min = 255;

	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {	
			Uint32 pixel = getpixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if(r > max) max = r;
			if(r < min) min = r;
		}
	}
	
	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			Uint32 pixel = getpixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			char npixel = ((r - min) * 255)/(max - min);

			pixel = SDL_MapRGB(img->format, npixel, npixel, npixel);
			putpixel(img, i, j, pixel);
		}
	}
	
	return img;
}

SDL_Surface* eq_hist(SDL_Surface* img) {
	
	long cum[256];
	for(int i = 0; i < 256; i++)
		cum[i] = 0;
	
	//img = norm(img);
	cum_hist(img, cum);
	
	//norm(img);

	double ratio = 255.0 / (img->h * img->w);

	for(int i = 0; i < img->w; i++) {
		for(int j = 0; j < img->h; j++) {
			Uint32 pixel = getpixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			char npixel = ratio * cum[r];
			//Uint8 npixel = cum[r];
			pixel = SDL_MapRGB(img->format, npixel, npixel, npixel);
			putpixel(img, i, j, pixel);
		}
	}
	return img;
}
