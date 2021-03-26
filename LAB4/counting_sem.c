/*********************************************************
 * Filename: counting_sem.c                              *
 * Description: Implements SPR21 CSCI-H 335 LAB4 Part 4  *
 * Author: Zachary E. Graber (zegraber@iu.edu)           *
 * Date: 3/26/2021                                       *
 *********************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

// Globals
sem_t sem;

void *pthread_A_routine() {
    sem_wait(&sem);
    printf("A\n");
    return NULL;
}

void *pthread_B_routine() {
    sem_wait(&sem);
    printf("B\n");
    return NULL;
}

void *pthread_C_routine() {
    sem_wait(&sem);
    printf("C\n");
    return NULL;
}

int main(void) {
    // Initialize the semaphore
    sem_init(&sem, 1, 2);
    
    sem_post(&sem); // FIX for code issue

    // Create the threads
    pthread_t tids[3];
    pthread_create(&tids[0], NULL, pthread_A_routine, NULL);
    pthread_create(&tids[1], NULL, pthread_B_routine, NULL);
    pthread_create(&tids[2], NULL, pthread_C_routine, NULL);

    // Join the threads
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);

    exit(EXIT_SUCCESS);
}