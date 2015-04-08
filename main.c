#include <stdlib.h>
#include "sdl_stuff.h"
#include "image_transf.h"

int main() {
	display_image(eq_hist(Greyscale(load_image("image.jpg"))));
}
