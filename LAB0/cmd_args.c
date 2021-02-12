#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Error: Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	printf("The argument is %s\n", argv[1]);
	exit(EXIT_SUCCESS);
}
