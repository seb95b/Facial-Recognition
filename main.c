#include <stdlib.h>
#include "sdl_stuff.h"
#include "image_transf.h"
#include "haar_features.h"

int main() {
	//SDL_Surface *img = eq_hist(Greyscale(load_image("image.jpg")));
	SDL_Surface *img = load_image("image.jpg");
	//display_image(img);
	
	int **int_image = malloc(img->h*sizeof(int*));
	for(int i = 0; i < img->h; i++) {
		int_image[i] = malloc(img->w*sizeof(int));
	}
	
	compute_int_image(int_image, img);
	
	for(int i = 0; i < img->h; i++) {
		for(int j = 0; j < img->w; j++) {
			printf(" %d ", int_image[i][j]);
		}
		
		printf("\n");
	}
}
