#ifndef ADABOOST_H
#define ADABOOST_H

#include <dirent.h>
#include <math.h>
#include "sdl_stuff.h"
#include "image_transf.h"
#include "haar_features.h"

struct image {
	int face;
	struct features *feat; //63960
};

struct ada_features {
	struct features *feat;
	int face;
};

struct weakclass {
	struct features f;
	int t; //threshold
	int p; // polarity
};

struct strongclass {
	struct weakclass *wc;
	float *alpha;
};

struct strongclass *adaboost(struct image *tab, unsigned int iter);

struct image *prepare_tab_image(int size, int nb);

#endif
