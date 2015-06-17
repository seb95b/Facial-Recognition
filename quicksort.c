#include <stdlib.h>
#include "quicksort.h"

int part(struct ada_features *tableau, int p, int r) {
    int pivot = tableau[p].feat, i = p-1, j = r+1;
    struct ada_features temp;
    while (1) {
        do j--; while (tableau[j].feat > pivot);
        do i++; while (tableau[i].feat < pivot);
        if (i < j) {
            temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
        }
        else
            return j;
    }
}
 
void quickSort(struct ada_features *tableau, int p, int r) {
    int q;
    if (p < r) {
        q = part(tableau, p, r);
        quickSort(tableau, p, q);
        quickSort(tableau, q+1, r);
    }
}
