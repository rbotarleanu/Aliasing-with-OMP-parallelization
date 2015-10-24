/* Botarleanu Robert-Mihai
 * 331CB
 */

#ifndef HOMEWORK1_HEADER_GUARD
#define HOMEWORK1_HEADER_GUARD

#include "omp.h"

// distance macro
#define distance(x ,y) (int) (abs(-1 * x + 2 * y + 0) / sqrt(1 + 4))

// constants
#define IMG_GRAYSCALE "P5"
#define WHITE 255
#define BLACK 0
#define PIXEL_COLOR_MAXVALUE 255

// aliases
enum { false, true };
typedef unsigned char byte;
typedef unsigned char bool;


/* Datatype for image struct.
 * Holds the resolution and the pixel matrix;
 */
 typedef struct img {
	int 			width;
	int			 	height;
	int 			maxval;
	byte** 			byte_array;
} image;

#endif