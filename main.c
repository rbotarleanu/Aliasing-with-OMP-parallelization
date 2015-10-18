/* Botarleanu Robert-Mihai 
 * 331CB
 */
#include "homework.h"

extern int num_threads;
extern int resize_factor;
int main(int argc, char * argv[]) {
	//agrv[1] input
	//argv[2] output
	//argv[3] resize_factor
	//argv[4] num_threads
	if(argc < 5)
		printf("Incorrect number of arguments\n");
	resize_factor = atoi(argv[3]);
	num_threads = atoi(argv[4]);

	image input;
	image output;

	readInput(argv[1], &input);

	double start = omp_get_wtime();
	resize(&input, &output);
	double end = omp_get_wtime();

	printf("%f\n",end-start);

	writeData(argv[2], &output);

}