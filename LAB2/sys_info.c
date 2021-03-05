/***********************************************************************
 * Filename: sys_info.c						       *
 * Description: Implements Spring 2021 CSCI-H 335 Lab 2 part 2	       *
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
	int fd[2];
	if (pipe(fd) == -1) {
		printf("ERROR: Could not create pipe!\n");
		exit(EXIT_FAILURE);
	}
	const int read_fd = fd[0], write_fd = fd[1];
	const char* path = "/bin/";
	
	const int pid = fork();
	if (pid < 0) {
		printf("ERROR: An error occurred while forking.\n");
		exit(EXIT_FAILURE);
	}

	// Parent process
	if (pid != 0) {
		char* exec = argv[1];
		// If the executable starts with /bin/, then remove it before writing to the pipe
		if (strncmp(exec, path, strlen(path)) == 0) {
			exec += strlen(path); // Move the pointer forward to get rid of /bin/
		}
		// First write to the pipe an int telling the child how many bytes to expect to read.
		int nbytes_1 = strlen(exec) + 1;
		write(write_fd, &nbytes_1, sizeof(int));

		// Write the executable to the pipe
		write(write_fd, exec, nbytes_1);
		
		// Write the argument to the pipe
		int nbytes_2 = strlen(argv[2]) + 1;
		write(write_fd, &nbytes_2, sizeof(int));
		write(write_fd, argv[2], nbytes_2);
		close(write_fd);
		exit(EXIT_SUCCESS);
	}

	// Child Process
	else {
		// Get the number of bytes to expect for arg1
		int nbytes_1;
		read(read_fd, &nbytes_1, sizeof(int));

		// Read the first argument
		char arg1_read[nbytes_1];
		read(read_fd, arg1_read, nbytes_1);

		// Get number of bytes to expect for arg2
		int nbytes_2;
		read(read_fd, &nbytes_2, sizeof(int));

		// Read the second argument
		char arg2_read[nbytes_2];
		read(read_fd, arg2_read, nbytes_2);
		
		// Close the read end of the pipe
		close(read_fd);

		// Construct the final path for the executable
		char path_final[nbytes_1 + strlen(path)];
		sprintf(path_final, "%s%s", path, arg1_read);

		// DEBUGGING
		// printf("path_final: %s, arg1_read: %s, arg2_read: %s\n", path_final, arg1_read, arg2_read);

		execl(path_final, arg1_read, arg2_read, NULL);
		exit(EXIT_SUCCESS);	
	}
}