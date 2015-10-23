/* Botarleanu Robert-Mihai 
 * 331CB
 */
#include "homework.h"

int num_threads;
int resize_factor;
const int gk[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };

void readInput(const byte * fileName, image *img) {
	int i, j;
	// attempt to open file
	FILE *fin = fopen(fileName, "r");

	// read magic number
	byte magic_number[MAGIC_NUMBER_SIZE];
	fscanf(fin, "%s\n", magic_number);

	// check image type
	if(!strcmp(magic_number, IMG_GRAYSCALE)) {
		img->grayscale = true;
	} else if(!strcmp(magic_number, IMG_COLOR)) {
		img->grayscale = false;
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

void construct_byte_array_even(image *in, image *out) {
	int i, j, out_i, out_j;
	int sum, r, g, b;

	// the number of pixels in this submatrix with which to compute the average
	const int cnt = resize_factor * resize_factor;

	// set the number of threads
	omp_set_num_threads(num_threads);

	// compute the byte array
	out_i = 0, out_j = 0;
	// if the image is grayscale then each submatrix will have size
	// resize_factor x resize_factor; if it is color then the width
	// will be 3 times as large to accomodate for the R,G,B values
	int step = resize_factor * ((out->grayscale)?1:3);
	// for each pixel in the upper left corner of a submatrix
	#pragma omp parallel for private(out_i, out_j, sum, r, g, b, i, j)
	for( i = 0 ; i <= in->height - resize_factor; i += resize_factor) {
		for(j = 0; j + step <= in->bytes_in_row; j += step) {
			int k, x;
			// sum, r, g, b are total sums of pixels in this submatrix
			// for grayscale/(R,G,B) colors
			sum = 0;
			r = 0, g = 0, b = 0;
			// go through each pixel in the submatrix
			for(k = i; k < i + resize_factor; ++k)
				for(x = j; x < j + step; x += (in->grayscale)?1:3) {
				if(!in->grayscale) {
						// add every color (R,G,G) separately
						r += in->byte_array[k][x];
						g += in->byte_array[k][x+1];
						b += in->byte_array[k][x+2];
					} else {
						// add to the grayscale average
						sum += in->byte_array[k][x];
					}
				}
			// find the corresponding indexes in the output pixel matrix
			out_i = i / resize_factor;
			out_j = j / resize_factor;
			if(in->grayscale) { 
				// average the pixel colors
				out->byte_array[out_i][out_j] = (byte) (sum / cnt);
			} else {
				// average each color separately
				out->byte_array[out_i][out_j] = (byte) (r / cnt);
				out->byte_array[out_i][out_j+1] = (byte) (g / cnt);
				out->byte_array[out_i][out_j+2] = (byte) (b / cnt);
			}
		}
	}
}


void construct_byte_array_3(image *in, image *out) {
	int i, j, out_i, out_j;
	int sum, cnt, r, g, b;

	// set the number of threads
	omp_set_num_threads(num_threads);

	// compute the byte array
	// if the image is grayscale then each submatrix will have size
	// resize_factor x resize_factor; if it is color then the width
	// will be 3 times as large to accomodate for the R,G,B values
	int step = resize_factor * ((out->grayscale)?1:3);
	// for each pixel in the upper left corner of a submatrix
	#pragma omp parallel for private(out_i, out_j, sum, r, g, b, i, j)
	for( i = 0 ; i <= in->height - resize_factor; i += resize_factor) {
		for(j = 0; j + step <= in->bytes_in_row; j += step) {
			int gk_i, gk_j;
			int k, x;
			// sum, r, g, b are total sums of pixels in this submatrix
			// for grayscale/(R,G,B) colors
			sum = 0;
			r = 0, g = 0, b = 0;
			// the number of pixels in this submatrix with which to compute
			// the average
			cnt = 16;
			// go through each pixel in the submatrix
			for(gk_i = 0, k = i; k < i + resize_factor; ++k, ++gk_i)
				for(gk_j = 0,x = j; x < j + step; x += (in->grayscale)?1:3, ++gk_j) {
				if(!in->grayscale) {
						// add every color (R,G,G) separately
						r += in->byte_array[k][x] * gk[gk_i][gk_j];
						g += in->byte_array[k][x+1] * gk[gk_i][gk_j];
						b += in->byte_array[k][x+2] * gk[gk_i][gk_j]; 
					} else {
						// add to the grayscale average
						sum += in->byte_array[k][x] * gk[gk_i][gk_j];
					}
				}
			// find the corresponding indexes in the output pixel matrix
			out_i = i / resize_factor;
			out_j = j / resize_factor;

			if(in->grayscale) { 
				// average the pixel colors
				out->byte_array[out_i][out_j++] = (byte) (sum / cnt % in->maxval);
			} else {
				// average each color separately
				out->byte_array[out_i][out_j] = (byte) (r / cnt);
				out->byte_array[out_i][out_j+1] = (byte) (g / cnt);
				out->byte_array[out_i][out_j+2] = (byte) (b / cnt);
			}
		}
	}
}


void resize(image *in, image * out) { 
	// set num threads
	omp_set_num_threads(num_threads);
	int i;
	// recompute the width and height
	out->width = in->width / resize_factor;
	out->height = in->height / resize_factor;
	// magic number and maxval do not change
	out->grayscale = in->grayscale;
	out->maxval = in->maxval;
	// set number of bytes in the new byte array and allocate
	out->byte_count = out->width * out->height * ((out->grayscale)?1:3);
	// number of bytes in a row of the matrix
	out->bytes_in_row = out->byte_count / out->height;
	out->byte_array = (byte**) calloc(out->height, sizeof(byte*));
	// alocate the new matrix
	#pragma omp parallel for
	for(i = 0; i < out->height; ++i) {
		out->byte_array[i] = (byte*) calloc(out->bytes_in_row, sizeof(byte));
	}
	// even scaling factor
	if(resize_factor %2 == 0) {
		// construct the new byte array by computing the average values of pixels
		// in each resize_factor x resize_factor submatrix;
		construct_byte_array_even(in, out);
	} else if(resize_factor == 3) {
		// resize image with gaussian kernel
		construct_byte_array_3(in, out);
	} 
}
