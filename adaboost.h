#ifndef ADABOOST_H
#define ADABOOST_H

#include <dirent.h>
#include <math.h>
#include "sdl_stuff.h"
#include "image_transf.h"
#include "haar_features.h"
#include "quicksort.h"

struct image {
	int face;
	struct features *feat; //63960
};

struct weakclass {
	struct features f;
	int t; //threshold
	int p; // polarity
};

struct strongclass {
	struct weakclass *wc;
	float *alpha;
	int nb;
};

struct strongclass *adaboost(struct image *tab, unsigned int iter);

struct image *prepare_tab_image(int size, int nb);

#endif
