/*******************************************************************************
 * Filename: fileIO.c
 * Description: implements CSCI-H 335 LAB1 Part 01
 * Author: Zachary E Graber (zegraber@iu.edu)
 * Date: 2/25/2021
 *******************************************************************************/

#define _POSIX_C_SOURCE 2000809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	// Verify that arguments are correct
	if (argc != 3) {
		printf("FATAL: Expected 2 positional arguments\n<filename> <search string>\n");
		exit(EXIT_FAILURE);
	}

	char* fname = argv[1];
	const char* targetString = argv[2];
	FILE* fp;

	// Make sure the file opens correctly
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("FATAL: Could not open file %s\n", fname);
		exit(EXIT_FAILURE);
	}
	
	size_t length;
	char* thisLine;
	int matchedLines = 0;
	while (getline(&thisLine, &length, fp) != -1) {
		// If targetString is a substring of thisLine, add one to the count
		if (strstr(thisLine, targetString) != NULL) {
			matchedLines++;
		}
	}
	printf("%d\n", matchedLines);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
