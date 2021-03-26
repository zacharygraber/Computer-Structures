/*********************************************************
 * Filename: prodcons_failure.c                          *
 * Description: Implements SPR21 CSCI-H 335 LAB4 Part 1  *
 * Author: Zachary E. Graber (zegraber@iu.edu)           *
 * Date: 3/26/2021                                       *
 *********************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

// Globals
int x;

void *pthread_routine(void* arg) {
    int n = *((int*) arg); // Cast arg back from void* to int* then dereference
    int i, rand_num;
    for (i = 0; i < n; i++) {
        rand_num = rand() % n;
        x = rand_num;
        printf("writer wrote: %d\n", rand_num);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR: Expected 1 positional argument <n>\n");
        exit(EXIT_FAILURE);
    }

    // Seed the RNG
    time_t t = time(NULL);
    srand((unsigned int) t);

    // Get the command-line arg
    const int n = atoi(argv[1]);
    if (n < 1) {
        printf("ERROR: n cannot be less than 1!\n");
        exit(EXIT_FAILURE);
    }

    // Create the thread and pass the void*-casted address of n
    pthread_t tid;
    pthread_create(&tid, NULL, pthread_routine, (void*) &n);

    // Print the values of x
    int i;
    for (i = 0; i < n; i++) {
        printf("main read: %d\n", x);
    }

    pthread_join(tid, NULL);
    exit(EXIT_SUCCESS);
}