/***********************************************************************
 * Filename: execl.c						       *
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
		printf("ERROR: expected 2 positional arguments:\n<exec> <arg>\n");
		exit(EXIT_FAILURE);
	}
	
	const char* path = "/bin/";
	char path_final[strlen(argv[1]) + strlen(path)];
	sprintf(path_final, "%s%s", path, argv[1]);

	//printf("path_final: '%s', cmd: '%s', arg: '%s'\n", path_final, argv[1], argv[2]);
	execl(path_final, argv[1], argv[2], NULL);
	exit(EXIT_SUCCESS);
}
