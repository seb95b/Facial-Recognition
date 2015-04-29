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

/*int compute_f(int x, int y, int type, int scale, int **int_image) {
	
	int feature;
	
	switch(type) {
		//f1
		case 1:
		///////////////	
			
			int a, b, c, d, e, f;
			
			a = (x-scale > 0 && y-scale > 0)?int_image[x-scale][y-scale]:0;
			b = (x > 0 && y > 0)?int_image[x][y]:0;
			c = (x > 0 && y-scale > 0)?int_image[x][y-scale]:0;
			d = (x-scale > 0 && y > 0)?int_image[x-scale][y]:0;
			e = (x+scale > 0 && y > 0)?int_image[x+scale][y]:0;
			f = (x+scale > 0 && y-scale > 0)?int_image[x+scale][y-scale]:0;
			
			int rect_light, rect_dark;
			
			rect_light = a+b-c-d;
			rect_dark = c+e-b-f;
			
			return rect_light - rect_dark;
			
		//////////////
		break;
		
		//f2
		case 2:
		/////////////
			
			int a, b, c, d, e, f;
			
			a = (x-scale > 0 && y-scale > 0)?int_image[x-scale][y-scale]:0;
			b = (x > 0 && y > 0)?int_image[x][y]:0;
			c = (x > 0 && y-scale > 0)?int_image[x][y-scale]:0;
			d = (x-scale > 0 && y > 0)?int_image[x-scale][y]:0;
			e = (x+scale > 0 && y > 0)?int_image[x+scale][y]:0;
			f = (x+scale > 0 && y-scale > 0)?int_image[x+scale][y-scale]:0;
		
			int rect_light, rect_dark;
			
			rect_light = c+e-f-b;
			rect_dark = a+b-c-d;
			
			return rect_light - rect_dark; 
		/////////////
		break;
		
		//f3
		case 3:
			
		break;
		
		//f4
		case 4:
		
		break;
		
		//f5
		case 5:
		
		break;
		
		default:
			return 0
		break;
			
	}
}*/
