#include <stdlib.h>
#include <time.h>
#include "sdl_stuff.h"
#include "image_transf.h"
#include "haar_features.h"

int main() {
	SDL_Surface *img = load_image("imagebis.jpg");
	//SDL_Surface *img = load_image("image.jpg");
	display_image(img);
	
	img = Greyscale(img);
	
	display_image(img);
	
	img = eq_hist(img);
	
	display_image(img);
	
	img = norm(img);
	
	display_image(img);
	
	unsigned int **int_image = malloc(img->h*sizeof(int*));
	for(int i = 0; i < img->h; i++) {
		int_image[i] = calloc(img->w, sizeof(int));
	}
	
	time_t t1 = time(NULL);
	
	compute_int_image(int_image, img);
	
	for(int i = 0; i < img->h; i++) {
		for(int j = 0; j < img->w; j++) {
			printf(" %d ", int_image[i][j]);
		}
		
		printf("\n");
	} 
	
	printf("Exec in %d s\n", (int) (time(NULL) - t1));
}
