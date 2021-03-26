/*********************************************************
 * Filename: prodcons_q.c                                *
 * Description: Implements SPR21 CSCI-H 335 LAB4 Part 5  *
 * Author: Zachary E. Graber (zegraber@iu.edu)           *
 * Date: 3/26/2021                                       *
 *********************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

#define BUF_SIZE 5

// Globals
char buf[BUF_SIZE]; // after writing increment write_to; After reading increment read_from
sem_t mutex, empty_slots, filled_slots;
int read_from, write_to; // Keep track of the front/back of the queue

void print_queue();

void *prod_upper_routine(void* arg) {
    const int LOWER_BOUND = 65, UPPER_BOUND = 91;
    int i, tid = *((int*) arg);
    char c;
    for (i = 0; i < BUF_SIZE; i++) {
        // Generate a char
        c = (char) ((rand() % (UPPER_BOUND - LOWER_BOUND)) + LOWER_BOUND);

        // Write it to the queue
        sem_wait(&empty_slots); // Block until there is an empty slot to write to
        sem_wait(&mutex); // Hold the mutex
        buf[write_to] = c;
        write_to = (write_to + 1) % BUF_SIZE; // Increment the front, wrapping
        printf("writer ID: %d, char written: %c\n", tid, c);
        //print_queue(); // DEBUG
        sem_post(&mutex); // Give up the mutex
        sem_post(&filled_slots); // Increment the number of spots that are filled
    }
    return NULL;
}

void *prod_lower_routine(void* arg) {
    const int LOWER_BOUND = 97, UPPER_BOUND = 123;
    int i, tid = *((int*) arg);
    char c;
    for (i = 0; i < BUF_SIZE; i++) {
        // Generate a char
        c = (char) ((rand() % (UPPER_BOUND - LOWER_BOUND)) + LOWER_BOUND);

        // Write it to the queue
        sem_wait(&empty_slots); // Block until there is an empty slot to write to
        sem_wait(&mutex); // Hold the mutex
        buf[write_to] = c;
        write_to = (write_to + 1) % BUF_SIZE; // Increment the front, wrapping
        printf("writer ID: %d, char written: %c\n", tid, c);
        //print_queue(); // DEBUG
        sem_post(&mutex); // Give up the mutex
        sem_post(&filled_slots); // Increment the number of spots that are filled
    }
    return NULL;
}

void *cons_routine(void* arg) {
    int i, tid = *((int*) arg);
    char c;
    for (i = 0; i < BUF_SIZE; i++) {
        // Read from the queue, but block until there is something to read
        sem_wait(&filled_slots);
        sem_wait(&mutex); // Grab the mutex
        c = buf[read_from];
        buf[read_from] = ' ';
        read_from = (read_from + 1) % BUF_SIZE; // Increment the back, wrapping
        printf("reader ID: %d, char read: %c\n", tid, c);
        //print_queue();
        sem_post(&mutex); // Release the mutex
        sem_post(&empty_slots); // Mark the spot as empty, since we've read it
    }
    return NULL;
}


int main(void) {
    // Seed the RNG
    time_t t = time(NULL);
    srand((unsigned int) t);

    // Initialize the semaphores and buffer front/back
    sem_init(&mutex, 1, 1);
    sem_init(&empty_slots, 1, BUF_SIZE);
    sem_init(&filled_slots, 1, 0);
    read_from = 0;
    write_to = 0;

    // Create the threads
    pthread_t tids[8];
    int writer_ids[] = {0,1,2,3};
    int reader_ids[] = {0,1,2,3};
    pthread_create(&tids[0], NULL, prod_lower_routine, (void*) &(writer_ids[0]));
    pthread_create(&tids[1], NULL, prod_lower_routine, (void*) &(writer_ids[1]));
    pthread_create(&tids[2], NULL, prod_upper_routine, (void*) &(writer_ids[2]));
    pthread_create(&tids[3], NULL, prod_upper_routine, (void*) &(writer_ids[3]));
    
    int i;
    for (i = 0; i < 4; i++) {
        pthread_create(&tids[i + 4], NULL, cons_routine, (void*) &(reader_ids[i]));
    }

    // Join the threads
    for (i = 0; i < 8; i++) {
        pthread_join(tids[i], NULL);
    }

    exit(EXIT_SUCCESS);
}

void print_queue() {
    int i;
    printf("[");
    for (i = 0; i < BUF_SIZE - 1; i++) {
        printf("%c, ", buf[i]);
    }
    printf("%c]\n", buf[BUF_SIZE - 1]);
    return;
}