/***********************************************************************
 * Filename: pipe_sp.c						       *
 * Description: Implements Spring 2021 CSCI-H 335 Lab 2 part 1	       *
 * Author: Zachary E. Graber (zegraber@iu.edu)			       *
 * Date: 3/5/2021						       *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR: Expected 2 positional arguments!\n");
		exit(EXIT_FAILURE);
	}
	int fd[2];
	pipe(fd);
	int read_fd = fd[0], write_fd = fd[1];

	int nbytes_arg1 = strlen(argv[1])+1, nbytes_arg2 = strlen(argv[2])+1;

	// For debugging	
	// printf("nbytes_arg1: %d, nbytes_arg2: %d\n\n", (int)nbytes_arg1, (int)nbytes_arg2);
	
	if (write(write_fd, argv[1], nbytes_arg1) != nbytes_arg1) {
		printf("ERROR: Could not write arg %s to pipe!\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (write(write_fd, argv[2], nbytes_arg2) != nbytes_arg2) {
		printf("ERROR: Could not write arg %s to pipe!\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	close(write_fd);

	char arg1_read[nbytes_arg1], arg2_read[nbytes_arg2];
	if (read(read_fd, arg1_read, nbytes_arg1) != nbytes_arg1) {
		printf("ERROR: Could not read arg %s from pipe!\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if (read(read_fd, arg2_read, nbytes_arg2) != nbytes_arg2) {
		printf("ERROR: Could not read arg %s from pipe!\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	close(read_fd);

	printf("%s\n", arg1_read);
	printf("%s\n", arg2_read);
	exit(EXIT_SUCCESS);
}
