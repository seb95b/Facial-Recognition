#include <stdlib.h>
#include "pixel_operations.h"
#include "haar_features.h"

/*void compute_int_image(unsigned int **int_image, SDL_Surface *img) { // exec in 42 s for an image of 252x350
		int width = img->w;
		int height = img->h;

		for(int x = 0; x < height; x++) {
				for(int y = 0; y < width; y++) {
						int result = 0;

						for(int i = 0; i <= x; i++) {
								for(int j = 0; j <= y; j++) {
										Uint32 pixel = getpixel(img, i, j);
										Uint8 r, g, b;
										SDL_GetRGB(pixel, img->format, &r, &g, &b);	
										result += r;
								}
						}

						int_image[x][y] = result;
				}
		}
}*/

int row_sum(int x, int y, SDL_Surface *img) {
	if(y >= 0) return row_sum(x, y-1, img) + getintensity(x, y, img);
	return 0;
}

int compute_int_image_rec(int x, int y, unsigned int **int_image, SDL_Surface *img) {
	if(x >= 0) {
		int_image[x][y] = compute_int_image_rec(x-1, y, int_image, img) + row_sum(x, y, img);
		return int_image[x][y];
	}
	return 0;
}

void compute_int_image(unsigned int **int_image, SDL_Surface *img) {
	for(int y = 0; y < img->w; y++) {
		compute_int_image_rec(img->h-1, y, int_image, img);
	}
}

int compute_f(int x, int y, int type, int scale, int **int_image) {
	//FIX ME
}
