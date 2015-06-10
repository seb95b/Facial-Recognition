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

static int compute_features(int x, int y, int type, int scale_x, int scale_y int **int_image){
	const int A = int_image[x-1][y-1];
	const int C = int_image[x-1][x + scale_y];
	const int B = int_image[x + scale_x][y -1];
	const int D = int_image[x + scale_x][y + scale_y];
	switch(type){
		case 0;
			return (A + D - C - B) - (B + int_image[x + 2*scale_x][y + 2*scale_y] - D - int_image[x + 2*scale_x][y - 1]);
		break;

		case 1;
			return (C + int_image[x + scale_x][y + 2*scale_y] - int_image[x-1][y + 2*scale_y] - D) - (A + D - C - B);
                break;

		case 2;
			return (a + D - C - B) - (B + int_image[x + 2*scale_x][y + scale_y] - D - int_image[][] ) + ()
                break;

		case 3;
			
                break;

		case 4;
			
                break;
	}
}

int compute_f(int **int_image){
	const int feature[features][2] = {{2,1}, {1,2}, {3,1}, {1,3}, {2,2}};
	const int frameSize = 19;
	struct features *tab_f = malloc(compute_size()*sizeof(struct features));
	int f = 0;
	for (int i = 0; i < 5; i++) {
		int sizeX = feature[i][0];
		int sizeY = feature[i][1];
        	for (int x = 0; x <= frameSize-sizeX; x++) {
			for (int y = 0; y <= frameSize-sizeY; y++) {
                        	for (int width = sizeX; width <= frameSize-x; width+=sizeX) {
                                        for (int height = sizeY; height <= frameSize-y; height+=sizeY) {
                                                tab_f[f] = compute_features(x,y,i, width, height, int_image);
						f++;
                                        }
                                }
			}
                }
        }
}
static int compute_size(){
	const int frameSize = 19;
        const int features = 5;
// All five feature types:
        const int feature[features][2] = {{2,1}, {1,2}, {3,1}, {1,3}, {2,2}};
        int count = 0;
// Each feature:
        for (int i = 0; i < features; i++) {
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
