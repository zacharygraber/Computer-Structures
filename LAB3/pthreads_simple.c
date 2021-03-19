/*********************************************************
 * Filename: pthreads_simple.c				 *
 * Description: Implements SPR20 CSCI-H 335 LAB3 Part 1  *
 * Author: Zachary E Graber (zegraber@iu.edu)            *
 * Date: 3/19/2021                                       *
 *********************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// Fallback value for INCCNT in case it is not defined in compilation
#ifndef INCCNT
	#define INCCNT 1000
#endif

void *pthread1_routine(void* arg) {
	const char* APPEND_STR = " Example";
	char* s = *((char**) arg); // Arg is the address of the char* (c-string) that has the argument, so a char**
	char result[strlen(s) + strlen(APPEND_STR) + 1];
	strcpy(result, s);
	strcat(result, APPEND_STR);
	printf("Concat String: %s\n", result);
	return NULL;
}

void *pthread2_routine(void* arg) {
	int n = *((int*) arg); // Cast arg to int* then dereference to get the int
	printf("Count: %d\n", n + INCCNT);
	return NULL;
}

int main (int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR: Expected 2 positional arguments <string> <int>\n");
		exit(EXIT_FAILURE);
	}

	char* arg1 = argv[1];
	int arg2 = atoi(argv[2]);
	
	pthread_t tids[2];
	pthread_create(&tids[0], NULL, pthread1_routine, (void*) &arg1);
	pthread_create(&tids[1], NULL, pthread2_routine, (void*) &arg2);

	pthread_join(tids[0], NULL);
	pthread_join(tids[1], NULL);
	exit(EXIT_SUCCESS);
}
