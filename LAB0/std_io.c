#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[]) {
	// less than 2 args means invalid args
	if (argc < 2) {
		printf("ERROR: Invalid arguments!\n");
		exit(EXIT_FAILURE);
	}
	
	// Now that we know there are at least 2 args...
	if (strcmp(argv[1], "scanf") == 0) {
		char buffer[99];
		printf("Please enter your input: ");
		scanf(" %s", buffer);
		printf("You entered: %s\n", buffer);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(argv[1], "printf") == 0 && argc > 2) {
		printf("You entered: %s\n", argv[2]);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(argv[1], "fprintf") == 0 && argc > 2) {
		FILE* f = fopen("print.txt", "w");
		if (f == NULL) {
			printf("ERROR: Error opening file print.txt for writing!\n");
			exit(EXIT_FAILURE);
		}

		if (fprintf(f, "%s", argv[2]) < 0) {
			printf("ERROR: Error writing to file print.txt!\n");
			exit(EXIT_FAILURE);
		}
		else if (fclose(f) != 0) {
			printf("ERROR: Error closing file print.txt!\n");
			exit(EXIT_FAILURE);
		}
		else {
			exit(EXIT_SUCCESS);
		}
	}
	else {
		printf("ERROR: Invalid arguments!\n");
		exit(EXIT_FAILURE);
	}	
}
