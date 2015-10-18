/* Botarleanu Robert-Mihai 
 * 331CB
 */
#include "homework.h"

int num_threads;
int resize_factor;

void readInput(const byte * fileName, image *img) {
	int i, j;
	// attempt to open file
	FILE *fin = fopen(fileName, "r");

	// file not found
	if(!fin) {
		fprintf(stderr, "File %s not found.\n", fileName);
		img = NULL;
		return;
	}

	// read magic number
	byte magic_number[MAGIC_NUMBER_SIZE];
	fscanf(fin, "%s\n", magic_number);

	// check image type
	if(!strcmp(magic_number, IMG_GRAYSCALE)) {
		img->grayscale = true;
	} else if(!strcmp(magic_number, IMG_COLOR)) {
		img->grayscale = false;
	} else {
		fprintf(stderr, "PNM header is invalid!\n");
		free(img);
		img = NULL;
		return;
	}

	// read with and height
	fscanf(fin, "%d %d\n", &img->width, &img->height);

	// set number of bytes in the byte array and allocate
	img->byte_count = img->width * img->height * ((img->grayscale)?1:3);
	// number of bytes in a row of the matrix
	img->bytes_in_row = img->byte_count / img->height;
	img->byte_array = (byte**) calloc(img->height, sizeof(byte*));
	for(i = 0; i < img->height; ++i) {
		img->byte_array[i] = (byte*) calloc(img->bytes_in_row, sizeof(byte));
	}

	// read maxval
	fscanf(fin, "%d\n", &img->maxval);
	
	// read byte array
	for(i = 0; i < img->height; ++i) {
		fread(img->byte_array[i], sizeof(byte), img->bytes_in_row, fin);
	}

	fclose(fin);
}

void writeData(const byte * fileName, image *img) {
	int i;
	// attempt to open file
	FILE *fout = fopen(fileName, "wb");
	printf("Writing file: %s\n", fileName);

	// failure
	if(!fout) {
		fprintf(stderr, "File %s not found.\n", fileName);
		img = NULL;
		return;
	}

	// write magic number
	fprintf(fout, "%s\n", (img->grayscale)?IMG_GRAYSCALE:IMG_COLOR);
	// write width and height
	fprintf(fout, "%d %d\n", img->width, img->height);
	// write maxval
	fprintf(fout, "%d\n", img->maxval);
	// write the byte array
	for(i = 0; i < img->height; ++i) {
		fwrite(img->byte_array[i], sizeof(byte), img->bytes_in_row, fout);
	}
	fclose(fout);
}

void resize(image *in, image * out) { 
	*out = *in;
}