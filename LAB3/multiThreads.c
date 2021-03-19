/*********************************************************
 * Filename: multiThreads.c				 *
 * Description: Implements SPR20 CSCI-H 335 LAB3 Part 2  *
 * Author: Zachary E Graber (zegraber@iu.edu)            *
 * Date: 3/19/2021                                       *
 *********************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>



void *pthread1_routine(void* arg) {
	
	return NULL;
}

void *pthread2_routine(void* arg) {
	
	return NULL;
}

int main (int argc, char* argv[]) {
	if (argc != 5) {
		printf("ERROR: Expected 4 positional arguments <filename 1> <search string 1> <filename 2> <search string 2>\n");
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
