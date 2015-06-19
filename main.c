#include <stdlib.h>
#include <time.h>
#include "adaboost.h"

int main() {

	time_t t1 = time(NULL);
	//SDL_Surface *img = load_image("imagebis.jpg");
	/*SDL_Surface *img = load_image("1919.png");
	//display_image(img);

	//img = Greyscale(img);

	//display_image(img);

	//img = eq_hist(img);

	//display_image(img);

	//img = norm(img);

	//display_image(img);

	unsigned int **int_image = malloc(img->h*sizeof(int*));
	for(int i = 0; i < img->h; i++) {
		int_image[i] = calloc(img->w, sizeof(int));
	}


	compute_int_image(int_image, img);
	//Test
	int size = compute_size(19);
	struct features *tab;
	tab = compute_f(19, int_image);
	for(int i = 0; i < img->h; i++) {
		for(int j = 0; j < img->w; j++) {
			printf(" %d ", int_image[i][j]);
		}

		printf("\n\n");
	} 

	for(int i = 0; i < size; i++){
		if(tab[i].type == 3) {
			printf("val: %d |", tab[i].val);
			printf(" x: %zu ", tab[i].x);
			printf("y: %zu ", tab[i].y);
			printf("scale_x: %zu ", tab[i].scale_x);
			printf("scale_y: %zu ", tab[i].scale_y);
			printf("type: %d \n", tab[i].type); 
		}
	}*/



	struct image *i = prepare_tab_image(19, 2);
	if(i[0].feat) {
		struct strongclass *strong = adaboost(i, 2);

		for(int j = 0; j < 2; ++j) {
			printf("%d ", strong->wc[j].f.type);
			printf("%zu ", strong->wc[j].f.x);
			printf("%zu ", strong->wc[j].f.y);
			printf("%zu ", strong->wc[j].f.scale_x);
			printf("%zu\n", strong->wc[j].f.scale_y);
		}
	}

	printf("Exec in %d s\n", (int) (time(NULL) - t1));
}
