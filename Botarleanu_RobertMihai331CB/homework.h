/* Botarleanu Robert-Mihai 
 * 331CB
 */

#ifndef HOMEWORK_HEADER_GUARD
#define HOMEWORK_HEADER_GUARD

// dependencies 
#include <omp.h>

// constants
#define MAGIC_NUMBER_SIZE 2 // P5 or P6
#define IMG_GRAYSCALE "P5"
#define IMG_COLOR "P6"

extern const int gk[3][3];

// aliases
enum { false, true };
typedef unsigned char byte;
typedef unsigned char bool;

/* Struct for the datatype "image".
 * Holds whether the image is in grayscale, the width and height, the
 * maximum value of a byte, the number of bytes that are in the byte matrix,
 * the number of bytes in one row of the matrix and the byte matrix.
 */
typedef struct img {
	int 			width;
	int			 	height;
	bool 			grayscale;
	int 			maxval;
	int 			byte_count;
	int 			bytes_in_row;
	byte** 			byte_array;
} image;

#endif
