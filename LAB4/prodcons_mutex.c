/*********************************************************
 * Filename: prodcons_mutex.c                            *
 * Description: Implements SPR21 CSCI-H 335 LAB4 Part 2  *
 * Author: Zachary E. Graber (zegraber@iu.edu)           *
 * Date: 3/26/2021                                       *
 *********************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

// Globals
int x;
sem_t r_mutex, w_mutex;

void *pthread_routine(void* arg) {
    int n = *((int*) arg); // Cast arg back from void* to int* then dereference
    int i, rand_num;
    for (i = 0; i < n; i++) {
        rand_num = rand() % n;
        sem_wait(&w_mutex);
        x = rand_num;
        sem_post(&r_mutex);
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
    //time_t t = time(NULL);
    //srand((unsigned int) t);

    // Get the command-line arg
    const int n = atoi(argv[1]);
    if (n == 0) {
        printf("ERROR: n cannot be 0!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    sem_init(&r_mutex, 1, 0); // We don't want to read until we've written first
    sem_init(&w_mutex, 1, 1); // But we can write right away

    // Create the thread and pass the void*-casted address of n
    pthread_t tid;
    pthread_create(&tid, NULL, pthread_routine, (void*) &n);

    // Print the values of x
    int i;
    for (i = 0; i < n; i++) {
        sem_wait(&r_mutex);
        printf("main read: %d\n", x);
        sem_post(&w_mutex);
    }

    pthread_join(tid, NULL);
    exit(EXIT_SUCCESS);
}