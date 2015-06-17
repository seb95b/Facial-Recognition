#ifndef QUICKSORT_H
#define QUICKSORT_H

struct ada_features {
	int feat;
	int face;
};

int part(struct ada_features *tableau, int p, int r);

void quickSort(struct ada_features *tableau, int p, int r);

#endif
