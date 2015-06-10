#include <stdlib.h>
#include <dirent.h>
#include <pixel_operations.h>
#include <math.h>
#include "adaboost.h"
#include "haar_features.h"
#include "quicksort.h"

int nb_features = 63960;

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

static int sp(struct ada_features feat) {
	int sp;
	for(sp = 0; sp < threshold; if(feat_t[sp].face) sp++);
	return sp;
}

static int sm(struct ada_features feat, int threshold) {
	int sm;
	for(sm = 0; sp < threshold; if(!feat_t[sm].face) sm++);
	return sm;
}

int compute_threshold(struct ada_features *feat_t, const int nb_neg, const int nb_pos) {
	quickSort(feat_t, 0, nb_features);
	
	int threshold;
	int *error = malloc((nb_neg+neg_pos)*sizeof(int));
	
	for(int i = 0; i < nb_neg+neg_pos; ++i) {
		
		threshold = feat_t[i].feat->val;
		
		int error1 = sp(feat_t, threshold)+(nb_neg - sm(feat_t, threshold));
		int error2 = sm(feat_t, threshold)+(nb_pos - sp(feat_t, threshold));
		
		int error[i] = (error1 < error2)?error1:error2;
	}
	
	int index = 0;
	int min_error = error[0];
	for(int i = 1; i < nb_neg+neg_pos; i++) {
		if(error[i] < min_error) {
			min_error = error[i];
			index = i;
		}
	}
	
	return feat_t[index].feat->val;
}

struct strongclass *adaboost(struct image *image_tab, unsigned int iter, unsigned int strong) {
	const int nb_neg;
	const int nb_pos;
	
	float *weight = malloc((nb_pos+nb_neg)*sizeof(float));
	
	struct strongclass *strongclassfier = malloc(sizeof(struct strongclass));
	strongclassifier->wc = malloc(strong*sizeof(struct weakclass));
	strongclassifier->alpha = malloc(strong*sizeof(float));
	
	struct weakclass *temp_weak = malloc(nb_feature*sizeof(struct weakclass));
	
	struct ada_features *feat_t = malloc((nb_pos+nb_neg)*sizeof(struct ada_features*));
	
	float *error = malloc(nb_features*sizeof(float));
	
	int i = 0;
	for(; i < nb_pos; ++i) {
		weight[i] = 1/nb_pos;
	}
	for(; i < nb_pos + nb_neg; ++i) {
		weight[i] = 1/nb_neg;
	}
	
	for(unsigned int t = 0; t < iter; ++t) { //main ada loop
		
		float sum = 0;//normalize weights
		for(unsigned int j = 0; j < nb_pos + nb_neg; ++j) {
			sum += weight[j];
		}
		for(unsigned int j = 0; j < nb_pos + nb_neg; ++j) {
			weight = weight[j]/sum;
		}
		
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
			
			temp_weak[i].f.x = image_tab[0].feat[i].x;
			temp_weak[i].f.y = image_tab[0].feat[i].y;
			temp_weak[i].f.scale_x = image_tab[0].feat[i].scale_x;
			temp_weak[i].f.scale_y = image_tab[0].feat[i].scale_y;
			temp_weak[i].f.type = image_tab[0].feat[i].type;
			temp_weak[i].t = threshold;
			temp_weak[i].p = polarity;
			
			error[i] = 0;
			for(unsigned int j = 0; j < nb_pos + nb_neg); ++j) { 
				error[i] += weight[j]*fabs((double) (compute_weakclass(threshold, polarity, image_tab[j].feat[i].val) - image_tab[j].face));
			}
		}
		
		float min_error = error[0];
		int index = 0;
		for(i = 1; i < nb_features; ++i) {
			if(error[i] < min_error) {
				min_error = error[i]; 
				index = i;
			}
		}
		
		struct weakclass *weakclassfier = malloc(sizeof(struct weakclass));
		weakclassifier->f = temp_weak[index].f;
		weakclassifier->t = temp_weak[index].t;
		weakclassifier->p = temp_weak[index].p;
		
		strongclassifier->wc[t] = weakclassfier;
		
		float beta = min_error/(1 - min_error);
			
		for(unsigned int j = 0; j < nb_pos + nb_neg; ++j) {
			weight[j] = weight[j]*pow(beta, 1-((compute_weakclass(threshold, polarity, image_tab[j].feat[index].val) == image_tab[j].face)?0:1));
		}
		
		strongclassifier->alpha[t] = log10(1/beta);
	}
	
	free(feat_t);
	free(weight);
	free(temp_weak);
	free(error);
	
	return strongclassifier;
}
