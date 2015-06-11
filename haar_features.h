#ifndef HAAR_FEATURES_H
#define HAAR_FEATURES_H

struct features {
	size_t x, y, scale_x, scale_y;
	int type, val;
};

int row_sum(int x, int y, SDL_Surface *img);

int compute_int_image_rec(int x, int y, unsigned int **int_image, SDL_Surface *img);

void compute_int_image(unsigned int **int_image, SDL_Surface *img);

int get_int_image(int x, int y, unsigned int **int_image);

int compute_features(int x, int y, int type, int scale_x, int scale_y , unsigned int **int_image);

struct features *compute_f(unsigned int **int_image);

int compute_size(int frameSize);

#endif
