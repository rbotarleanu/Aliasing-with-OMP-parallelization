/* Botarleanu Robert-Mihai
 * 331CB
 */

#include "homework1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int num_threads;
int resolution;

double calculateDistance(int x, int y) {
    return (abs(-1 * x + 2 * y + 0) / sqrt(1 + 4));
}

bool pixel_is_within_3m(int i, int j) {
	return (distance(
		            j * (100.0/resolution) + (100.0/resolution/2), 
			        i * (100.0/resolution) + (100.0/resolution/2)
			) < 3);
}

void initialize(image *im) {
	int i;
	// set the dimensions
	im->width = resolution;
	im->height = resolution;
	// set the maxvalue
	im->maxval = PIXEL_COLOR_MAXVALUE;
	// allocate the pixel array
	im->byte_array = (byte**) calloc(im->height, sizeof(byte*));
	omp_set_num_threads(num_threads);
	#pragma omp parallel for
	for(i = 0; i < im->height; ++i) {
		im->byte_array[i] = (byte*) calloc(im->width, sizeof(byte));
	}
}

void render(image *im) {
	int i, j;
	omp_set_num_threads(num_threads);
	#pragma omp parallel for private(j)
	for(i = 0; i < im->height; ++i) {
		for(j = 0; j < im->width; ++j)
			if(pixel_is_within_3m(resolution - 1 - i, j)) {
				im->byte_array[i][j] = BLACK;
			} else im->byte_array[i][j] = WHITE;
	}
}

void writeData(const char * fileName, image *img) {
	int i;
	// attempt to open file
	FILE *fout = fopen(fileName, "w");
	// write magic number
	fprintf(fout, "%s\n", IMG_GRAYSCALE);
	// write width and height
	fprintf(fout, "%d %d\n", img->width, img->height);
	// write maxval
	fprintf(fout, "%d\n", img->maxval);
	// write the byte array
	for(i = 0; i < img->height; ++i) {
		fwrite(img->byte_array[i], sizeof(byte), img->width, fout);
	}
	fclose(fout);
}

