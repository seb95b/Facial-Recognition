#include <stdio.h>
#include <stdlib.h>

struct my_struct {
	int val;
	char nom[10];
};

void write(void* my_struct, size_t size, char* fichier)
{	
	FILE *fichier;
	fichier = fopen(fichier, "wb+");
	fwrite(my_struct, size, 1, fichier);
	
	fclose(fichier);
}

void read(void* my_struct, size_t size, char* fichier) {
	fichier = fopen(fichier, "rb");

	fread(my_struct, size, 1, fichier);
}
