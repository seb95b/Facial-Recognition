#include <stdlib.h>
#include <dirent.h>
#include <pixel_operations.h>
#include <math.h>
#include "adaboost.h"
#include "haar_features.h"
#include "quicksort.h"

unsigned int nb_features = 63960;

struct image *prepare_tab_image(size_t nb) {
	
	unsigned int **int_image = malloc(19*sizeof(int*));
	for(int i = 0; i < 19; i++) {
		int_image[i] = calloc(19, sizeof(int));
	}
	
	struct image *tab_image = malloc(nb*sizeof(struct image));
	
	int i = 0;

	DIR* rep = NULL;
    struct dirent* file = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    rep = opendir("./pos");
	
	if (rep == NULL) {
		printf("Erreur lors de la lecture du dossier pos");
        exit(1);
	}
	
    while(file = readdir(rep)) {
		SDL_Surface *img = load_image(file);
		img = Greyscale(img);
		img = eq_hist(img);
		
		compute_int_image(int_image, img);
		
		struct features *feat = compute_features(int_image);
		
		struct image pict;
		pict.face = 1;
		pict.feat = feat;
		
		tab_image[i] = pict;
		
		++i;
	}

    if (closedir(rep) == -1)
        exit(-1);
	
	rep = NULL;
	file = NULL;
	rep = opendir("./neg");
	
	if (rep == NULL) {
		printf("Erreur lors de la lecture du dossier neg");
        exit(1);
	}
	
	while(file = readdir(rep)) {
		SDL_Surface *img = load_image(file);
		img = Greyscale(img);
		img = eq_hist(img);
		
		compute_int_image(int_image, img);
		
		struct features *feat = compute_features(int_image);
		
		struct image pict;
		pict.face = 0;
		pict.feat = feat;
		
		tab_image[i] = pict;
		
		++i;
	}
	
	if (closedir(rep) == -1)
        exit(-1);
	
	for(int i = 0; i < 19; i++) { //free int_image
		free(int_image[i]);
	}
	free(int_image);
	
	return tab_image;
}

int compute_weakclass(int threshold, int polarity, int features) {
	if(polarity)
		return (features < threshold)?1:0;
	else
		return (feature > threshold)?1:0;
}

struct strongclass *adaboost(struct image *image_tab, unsigned int iter) {
	const int nb_neg;
	const int nb_pos;
	
	float *weight = malloc((nb_pos+nb_neg)*sizeof(float));
	
	int i = 0;
	for(; i < nb_pos; ++i) {
		weight[i] = 1/nb_pos;
	}
	for(; i < nb_pos + nb_neg; ++i) {
		weight[i] = 1/nb_neg;
	}
	
	for(unsigned int t = 0; t < iter; ++t) { //main ada loop
		
		float sum = 0;
		for(unsigned int j = 0; j < nb_pos + nb_neg; ++j) {
			sum += weight[j];
		}
		for(unsigned int j = 0; j < nb_pos + nb_neg; ++j) {
			weight = weight[j]/sum;
		}
		
		struct ada_features *feat_t = malloc((nb_pos+nb_neg)*sizeof(struct ada_features*));
		float *error = malloc(nb_features*sizeof(float));
		for(i = 0; i < nb_features; ++i) {
			for(unsigned int j = 0; j < nb_pos + nb_neg); ++j) {
				struct ada_features a_feat;
				a_feat.face = image_tab[j].face;
				a_feat.feat = (image_tab[j].feat)+i;
				feat_t[j] = a_feat;
			}
			
			int threshold = compute_threshold(feat_t);
			
			for(int sp = 0; sp < threshold; if(feat_t[sp].face) sp++);
			
			for(int sm = 0; sm < threshold, if(!feat_t[sm].face) sm++);
			
			int polarity = (sp > sm)?1:0; 
			
			error[i] = 0;
			for(unsigned int j = 0; j < nb_pos + nb_neg); ++j) { 
				error[i] += weight[j]*fabs((double) (compute_weakclass(threshold, polarity, image_tab[j].feat[i].val) - image_tab[j].face));
			}
		}
		
	}	
}
