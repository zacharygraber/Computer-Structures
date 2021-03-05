/***********************************************************************
 * Filename: pipe_mp.c						       *
 * Description: Implements Spring 2021 CSCI-H 335 Lab 2 part 1	       *
 * Author: Zachary E. Graber (zegraber@iu.edu)			       *
 * Date: 3/5/2021						       *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: Expected 1 positional argument!\n");
		exit(EXIT_FAILURE);
	}
	int fd[2];
	pipe(fd);
	int read_fd = fd[0], write_fd = fd[1];

	const int nbytes = strlen(argv[1]);
	
	int pid = fork();

	if (pid != 0) {
		if (write(write_fd, argv[1], nbytes) != nbytes) {
			printf("ERROR: Could not write arg %s to pipe!\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		close(write_fd);
		exit(EXIT_SUCCESS);
	}
	else {
		char arg_read[nbytes];
		if (read(read_fd, arg_read, nbytes) != nbytes) {
			printf("ERROR: Could not read arg %s from pipe!\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		close(read_fd);
		printf("%s\n", arg_read);
		exit(EXIT_SUCCESS);
	}
}
