#ifndef HAAR_FEATURES_H
#define HAAR_FEATURES_H

struct features {
	int x;
	int y;
	int val;
	struct features *next;
};

static inline int fvalue(struct features *f) { return f->val; }

void compute_int_image(int **int_image, SDL_Surface *img);

int count_features(int size);

void compute_features(struct features *f, int **int_image, int frameSize, int scale);

int compute_f(int x, int y, int type, int scale int **int_image);

#endif
