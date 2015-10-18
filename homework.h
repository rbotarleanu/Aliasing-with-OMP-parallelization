/* Botarleanu Robert-Mihai 
 * 331CB
 */

#ifndef HOEMEWORK_HEADER_FILE
#define HOEMEWORK_HEADER_FILE

#define MAGIC_NUMBER_SIZE 2 // P5 or P6
#define IMG_GRAYSCALE "P5"
#define IMG_COLOR "P6"

// debugging macros
#define DEBUG_ON 1
#define log_int(a)      if(DEBUG_ON) printf("%d\n", a)
#define log_char(a)    if(DEBUG_ON) printf("%c\n", a)
#define log_string(a)   if(DEBUG_ON) printf("%s\n", a)

// dependencies 
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

// constants
#define P5 "P5"
#define P6 "P6"

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