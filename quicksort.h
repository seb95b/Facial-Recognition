#ifndef QUICKSORT_H
#define QUICKSORT_H

#ifndef ADABOOST_H
struct ada_features {
	struct features *feat;
	int face;
};

struct features {
	size_t x, y, scale_x, scale_y;
	short type;
	int val;
};
#endif

int part(struct ada_features *tableau, int p, int r);

void quickSort(struct ada_features *tableau, int p, int r);

#endif
