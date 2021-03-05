/***********************************************************************
 * Filename: fork.c						       *
 * Description: Implements Spring 2021 CSCI-H 335 Lab 2 part 1	       *
 * Author: Zachary E. Graber (zegraber@iu.edu)			       *
 * Date: 3/5/2021						       *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int input;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: Expected 1 positional argument");
		exit(EXIT_FAILURE);
	}

	input = atoi(argv[1]);
	int pid = fork();
	printf("Hello World\n");
	
	// Child
	if (pid == 0) {
		printf("Child: %d\n", --input);
	}
	// Parent
	else {
		printf("Parent: %d\n", ++input);
	}
	exit(EXIT_SUCCESS);
}
