/*******************************************************************************
 * Filename: singleThread.c
 * Description: implements CSCI-H 335 LAB1 Part 02
 * Author: Zachary E Graber (zegraber@iu.edu)
 * Date: 2/25/2021
 *******************************************************************************/

#define _POSIX_C_SOURCE 2000809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	// Verify that arguments are correct
	if (argc != 5) {
		printf("FATAL: Expected 4 positional arguments\n<filename> <search string> <filename 2> <search string 2>\n");
		exit(EXIT_FAILURE);
	}

	char* fname = argv[1];
	char* targetString = argv[2];
	FILE* fp;

	// First file

	// Make sure the file opens correctly
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("FATAL: Could not open file %s\n", fname);
		exit(EXIT_FAILURE);
	}
	
	size_t length;
	char* thisLine;
	int matches = 0;
	while (getline(&thisLine, &length, fp) != -1) {
		// Find the first occurrence (if any) of the targetString in thisLine and save it back in thisLine
		while ((thisLine = strstr(thisLine, targetString)) != NULL) {
			matches++;
			// Increment the pointer so it doesn't "find" the same instance again and get stuck.
			thisLine++;
		}
	}
	printf("%s Count: %d\n", targetString, matches);

	// Second File

	fname = argv[3];
	targetString = argv[4];
	// Make sure the file opens correctly
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("FATAL: Could not open file %s\n", fname);
		exit(EXIT_FAILURE);
	}


	matches = 0;
	while (getline(&thisLine, &length, fp) != -1) {
		// If targetString is a substring of thisLine, add one to the count
		while ((thisLine = strstr(thisLine, targetString)) != NULL) {
			matches++;
			thisLine++;
		}
	}
	printf("%s Count: %d\n", targetString, matches);


	exit(EXIT_SUCCESS);
}
