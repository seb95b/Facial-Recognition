#ifndef HAAR_FEATURES_H
#define HAAR_FEATURES_H

struct features {
	size_t x, y, scale_x, scale_y;
	short type;
	int val;
};

static inline int fvalue(struct features *f) { return f->val; }

void compute_int_image(unsigned int **int_image, SDL_Surface *img);

int compute_int_image_rec(int x, int y, unsigned int **int_image, SDL_Surface *img);

int row_sum(int x, int y, SDL_Surface *img);

int count_features(int size);

void compute_features(struct features *f, int **int_image, int frameSize, int scale);

struct features *compute_f(unsigned int **int_image);

#endif
