#include <stdlib.h>
#include "pixel_operations.h"
#include "haar_features.h"

/*void compute_int_image(unsigned int **int_image, SDL_Surface *img) { // exec in 42 s for an image of 252x350
		int width = img->w;
		int height = img->h;

		for(int x = 0; x < height; x++) {
				for(int y = 0; y < width; y++) {
						int result = 0;

						for(int i = 0; i <= x; i++) {
								for(int j = 0; j <= y; j++) {
										Uint32 pixel = getpixel(img, i, j);
										Uint8 r, g, b;
										SDL_GetRGB(pixel, img->format, &r, &g, &b);	
										result += r;
								}
						}

						int_image[x][y] = result;
				}
		}
}*/

int row_sum(int x, int y, SDL_Surface *img) {
	if(y >= 0) return row_sum(x, y-1, img) + getintensity(x, y, img);
	return 0;
}

int compute_int_image_rec(int x, int y, unsigned int **int_image, SDL_Surface *img) {
	if(x >= 0) {
		int_image[x][y] = compute_int_image_rec(x-1, y, int_image, img) + row_sum(x, y, img);
		return int_image[x][y];
	}
	return 0;
}

void compute_int_image(unsigned int **int_image, SDL_Surface *img) {
	for(int y = 0; y < img->w; y++) {
		compute_int_image_rec(img->h-1, y, int_image, img);
	}
}
int get_int_image(int x, int y, unsigned int **int_image){
	const int framesize = 3;
	if(x < 0){
		return 0;
	}
	if(y < 0){
		return 0;
	}
	if(x >= framesize){
		return 0;
	}
	if(y >= framesize){
		return 0;
	}
	return int_image[x][y];
}
int compute_features(int x, int y, int type, int scale_x, int scale_y , unsigned int **int_image){
	if (type == 0){
		int Aa = get_int_image(x- 1, y- 1, int_image);
		int Ba = get_int_image(x + (scale_x/2)- 1, y- 1, int_image);
		int Ca = get_int_image(x- 1, y + scale_y- 1, int_image);
		int Da = get_int_image(x + (scale_x/2)- 1, y + (scale_y)- 1, int_image);
		int asquare11 = Aa + Da - Ca - Ba;
		int asquare21 = Ba + get_int_image(x + scale_x - 1, y + scale_y- 1, int_image) - Da - get_int_image(x + scale_x- 1, y- 1, int_image);
		return asquare11 - asquare21;
	}
 	if(type == 1){
		int Ab = get_int_image(x- 1, y- 1, int_image);
                int Bb = get_int_image(x + scale_x- 1, y- 1, int_image);
                int Cb = get_int_image(x- 1, y + scale_y/2- 1, int_image);
                int Db = get_int_image(x + scale_x- 1, y + (scale_y/2)- 1, int_image);
		int bsquare11 = Ab + Db - Cb - Bb;
		int bsquare12 = Cb + get_int_image(x + scale_x- 1, y + scale_y- 1, int_image) - get_int_image(x- 1, y + scale_y- 1, int_image) - Db;
		return bsquare12 - bsquare11;
   	}
	if(type == 2){
		int Ac = get_int_image(x- 1, y- 1, int_image);
                int Bc = get_int_image(x + (scale_x/3)- 1, y- 1, int_image);
      	        int Cc = get_int_image(x- 1, y + (scale_y)- 1, int_image);
                int Dc = get_int_image(x + (scale_x/3)- 1, y + scale_y- 1, int_image);
		int csquare11 = Ac + Dc - Cc - Bc;
        	int csquare21 = Bc+ get_int_image(x + 2*(scale_x/3)- 1, y + scale_y- 1, int_image) - Dc - get_int_image(x + 2*(scale_x/3)- 1, y- 1, int_image);
		int csquare31=get_int_image(x + 2*(scale_x/3)- 1,y- 1,int_image)+get_int_image(x+scale_x- 1,y+scale_y- 1,int_image)-get_int_image(x+2*(scale_x/3)- 1,y+scale_y- 1,int_image)-get_int_image(x+scale_x- 1,y- 1,int_image);
		return csquare11 - csquare21 + csquare31;
 	}
	if(type == 3){
		int Ad = get_int_image(x- 1, y- 1, int_image);
                int Bd = get_int_image(x + scale_x- 1, y- 1, int_image);
                int Cd = get_int_image(x- 1, y + (scale_y/3)- 1, int_image);
                int Dd = get_int_image(x + scale_x- 1, y + (scale_y/3)- 1, int_image);
		int dsquare11 = Ad + Dd - Cd - Bd;
		int dsquare12 = Cd + get_int_image(x + scale_x -1, y + 2*(scale_y/3) -1, int_image) - get_int_image(x-1, y + 2*(scale_y/3)-1, int_image) - Dd;
		int dsquare13=get_int_image(x -1,y+2*(scale_y/3)-1,int_image)+get_int_image(x+scale_x-1,y+scale_y-1,int_image)-get_int_image(x+scale_x-1,y+2*(scale_y/3)-1,int_image)-get_int_image(x-1,y+scale_y-1,int_image);
		return dsquare11 - dsquare12 + dsquare13;
    	}
	if(type == 4){
		int Ae = get_int_image(x- 1, y- 1, int_image);
       	        int Be = get_int_image(x + (scale_x/2)-1, y- 1, int_image);
                int Ce = get_int_image(x- 1, y + (scale_y/2)-1, int_image);
                int De = get_int_image(x + (scale_x/2)-1, y + (scale_y/2)-1, int_image);
		int esquare11 = Ae + De - Ce - Be;
		int esquare21 = get_int_image(x-1+scale_x/2,y-1,int_image)+get_int_image(x+scale_x-1,y+scale_y/2-1,int_image)-get_int_image(x+scale_x/2-1,y+scale_y/2-1,int_image)-get_int_image(x+scale_x-1,y-1,int_image);
		int esquare12 = get_int_image(x-1,y+scale_y/2-1,int_image)+get_int_image(x+scale_x/2-1,y+scale_y-1,int_image)-get_int_image(x+scale_x/2-1,y+scale_y/2-1,int_image)-get_int_image(x-1,y+scale_y-1,int_image);
		int esquare22 = De + get_int_image(x+scale_x-1,y+scale_y-1, int_image) - get_int_image(x + (scale_x/2)-1, y + scale_y-1, int_image) - get_int_image(x+scale_x-1,y+(scale_y/2)-1,int_image);
		return esquare21 - esquare11 + esquare12 - esquare22;
	}
return 0;
}

struct features *compute_f(unsigned int **int_image){
	const int feature[5][2] = {{2,1}, {1,2}, {3,1}, {1,3}, {2,2}};
	const int frameSize = 3;
	struct features *tab_f = malloc(compute_size(frameSize)*sizeof(struct features));
	int f = 0;
	for (int i = 0; i < 5; i++) {
		int sizeX = feature[i][0];
		int sizeY = feature[i][1];
        	for (int x = 0; x <= frameSize-sizeX; x++) {
			for (int y = 0; y <= frameSize-sizeY; y++) {
                        	for (int width = sizeX; width <= frameSize-x; width+=sizeX) {
                                        for (int height = sizeY; height <= frameSize-y; height+=sizeY) {
                                                tab_f[f].val = compute_features(x,y,i, width, height, int_image);
						tab_f[f].x = x;
                                                tab_f[f].y = y;
                                                tab_f[f].scale_x = width;
                                                tab_f[f].scale_y = height;
                                                tab_f[f].type = i;
						f++;
                                        }
                                }
			}
                }
        }
	return tab_f;
}
int compute_size(int frameSize){
// All five feature types:
        const int feature[5][2] = {{2,1}, {1,2}, {3,1}, {1,3}, {2,2}};
        int count = 0;
// Each feature:
        for (int i = 0; i < 5; i++) {
                int sizeX = feature[i][0];
                int sizeY = feature[i][1];
    // Each position:
                for (int x = 0; x <= frameSize-sizeX; x++) {
                        for (int y = 0; y <= frameSize-sizeY; y++) {
            // Each size fitting within the frameSize:
                                for (int width = sizeX; width <= frameSize-x; width+=sizeX) {
                                        for (int height = sizeY; height <= frameSize-y; height+=sizeY) {
                                                count++;
                                        }
                                }
                        }
                }
        }
	return count;
}
