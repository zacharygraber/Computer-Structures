/*********************************************************
 * Filename: fork_sum.c 				 *
 * Description: Implements SPR20 CSCI-H 335 LAB3 Part 3  *
 * Author: Zachary E Graber (zegraber@iu.edu)            *
 * Date: 3/19/2021                                       *
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Fallback value for ASIZE in case it is not defined in compilation
#ifndef ASIZE
	#define ASIZE 1000
#endif

int main (int argc, char* argv[]) {
	// Handle command-line arguments
	if (argc != 2) {
		printf("ERROR: Expected 1 positional argument <initial value>\n");
		exit(EXIT_FAILURE);
	}
	int init_val = atoi(argv[1]);

	// Make the array
	int array[ASIZE];
	for (int i = 0; i < ASIZE; i++) {
		array[i] = i * init_val;
	}

	// Open up a pipe for the child to communicate back to the parent
	int fd[2];
	if (pipe(fd) == -1) {
		printf("Could not open pipe!\n");
		exit(EXIT_FAILURE);
	}
	const int read_fd = fd[0], write_fd = fd[1];

	pid_t pid = fork();
	if (pid < 0) {
		printf("An error occurred while forking.\n");
		exit(EXIT_FAILURE);
	}

	// Child
	// The child always handles indices ASIZE/2 (inclusive) to ASIZE (exclusive)
	if (pid == 0) {
		close(read_fd); // The child doesn't need to read from the pipe, only write
		int sum = 0;
		for (int i = ASIZE / 2; i < ASIZE; i++) {
			sum += array[i];
		}
		write(write_fd, &sum, sizeof(int)); // Write the found sum to the pipe
	}
	// Parent
	// The parents always handles indices 0 (inclusive) to ASIZE/2 (exclusive)
	else {
		close(write_fd); // The parent never writes to the pipe
		int sum = 0;
		for (int i = 0; i < ASIZE / 2; i++) {
			sum += array[i];
		}

		// Read the child's sum
		int child_sum;
		read(read_fd, &child_sum, sizeof(int));

		// Add the two and print
		int final_sum = sum + child_sum;
		printf("%d", final_sum);
	}

	exit(EXIT_SUCCESS);
}
