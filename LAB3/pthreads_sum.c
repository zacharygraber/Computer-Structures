/*********************************************************
 * Filename: pthreads_sum.c 				 *
 * Description: Implements SPR20 CSCI-H 335 LAB3 Part 4  *
 * Author: Zachary E Graber (zegraber@iu.edu)            *
 * Date: 3/19/2021                                       *
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fallback value for ASIZE in case it is not defined in compilation
#ifndef ASIZE
	#define ASIZE 1000
#endif

// Fallback value for NTHREADS
#ifndef NTHREADS
	#define NTHREADS 2
#endif

int thread_sums[NTHREADS]; // Global variable to handle communicating threads' sums back to the main
int array[ASIZE]; // Declare the array as global so that all threads can access it.

void *pthread_routine(void* arg) {
	int tid = *((int*) arg); // Cast arg to an int*, then dereference it
	int increment = ASIZE / NTHREADS; // Integer division
	int start_index = increment * tid; // Start at increment * tid (inclusive)
	// Go for increment indices, unless it's the last, then just go to the end.
	int stop_index;
	if (tid == NTHREADS - 1)
		stop_index = ASIZE;
	else
		stop_index = increment * (tid + 1);

	// For debugging
	// printf("Thread %d handling [%d, %d)\n", tid, start_index, stop_index);

	// Sum up the elements this thread is responsible for
	int sum = 0;
	for (int i = start_index; i < stop_index; i++) {
		sum += array[i];
	}
	// Write this thread's findings to thread_sums in the respective index.
	thread_sums[tid] = sum;
	return NULL;
}

int main (int argc, char* argv[]) {
	// Handle command-line arguments
	if (argc != 2) {
		printf("ERROR: Expected 1 positional argument <initial value>\n");
		exit(EXIT_FAILURE);
	}
	int init_val = atoi(argv[1]);

	// Make the array
	for (int i = 0; i < ASIZE; i++) {
		array[i] = i * init_val;
	}

	// Create NTHREADS number of threads, and pass each their assigned index
	pthread_t tids[NTHREADS];
	int indices[NTHREADS];
	for (int i = 0; i < NTHREADS; i++) {
		indices[i] = i;
		pthread_create(&tids[i], NULL, pthread_routine, (void*) &(indices[i]));
	}

	// Reap the threads
	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(tids[i], NULL);
	}

	// Make the final sum
	int final_sum = 0;
	for (int i = 0; i < NTHREADS; i++) {
		final_sum += thread_sums[i];
	}
	printf("%d", final_sum);

	exit(EXIT_SUCCESS);
}
