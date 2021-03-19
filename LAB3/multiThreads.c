/*********************************************************
 * Filename: multiThreads.c				 *
 * Description: Implements SPR20 CSCI-H 335 LAB3 Part 2  *
 * Author: Zachary E Graber (zegraber@iu.edu)            *
 * Date: 3/19/2021                                       *
 *********************************************************/

#define _POSIX_C_SOURCE 2000809L
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

typedef struct input_args {
	char* fname;
	char* search_string;
} IA;

void *pthread_routine(void* arg) {
	IA *args_p = (IA*) arg; // Arg contains the address of an IA struct, so cast it to a struct pointer
	char* fname = args_p->fname;
	char* search_string = args_p->search_string;

	// Open the file
	FILE* fp;
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("ERROR: could not open file %s. Aborting thread.\n", fname);
		return NULL;
	}

	// Read it
	size_t length = 0;
	char* thisLine = NULL;
	char* temp;
	int targetLen = strlen(search_string);
	int matches = 0;
	while (getline(&thisLine, &length, fp) != -1) {
		temp = thisLine;
		// Find the first occurrence (if any) of the search string in thisLine and save it back in thisLine
		while ((temp = strstr(temp, search_string)) != NULL) {
			matches++;
		 	// Increment the pointer so it doesn't "find" the same instance again and get stuck.
		 	temp += targetLen;
		}
	}

	// Close the file and finish up
	fclose(fp);
	printf("%s Count: %d\n", search_string, matches);
	return NULL;
}

int main (int argc, char* argv[]) {
	if (argc != 5) {
		printf("ERROR: Expected 4 positional arguments <filename 1> <search string 1> <filename 2> <search string 2>\n");
		exit(EXIT_FAILURE);
	}

	IA arg1 = {argv[1], argv[2]};
	IA arg2 = {argv[3], argv[4]};
	
	pthread_t tids[2];
	pthread_create(&tids[0], NULL, pthread_routine, (void*) &arg1);
	pthread_create(&tids[1], NULL, pthread_routine, (void*) &arg2);

	pthread_join(tids[0], NULL);
	pthread_join(tids[1], NULL);
	exit(EXIT_SUCCESS);
}
