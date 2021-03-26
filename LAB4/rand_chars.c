/*********************************************************
 * Filename: rand_chars.c                                *
 * Description: Implements SPR21 CSCI-H 335 LAB4 Part 3  *
 * Author: Zachary E. Graber (zegraber@iu.edu)           *
 * Date: 3/26/2021                                       *
 *********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CHARS 10

// Function stubs
void print_upper_char();
void print_lower_char();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ERROR: Expected 1 argument! Use --help for more info!\n");
        exit(EXIT_FAILURE);
    }

    // Seed the RNG
    time_t t = time(NULL);
    srand((unsigned int) t);

    // Check what the arg is and do according behavior
    int i;
    char* arg = argv[1];
    if (strcmp(arg, "-u") == 0) {
        for (i = 0; i < NUM_CHARS; i++) {
            print_upper_char();
        }
    }
    else if (strcmp(arg, "-l") == 0) {
        for (i = 0; i < NUM_CHARS; i++) {
            print_lower_char();
        }
    }
    else if (strcmp(arg, "--help") == 0) {
        printf("Possible arguments:\n\t-u: print uppercase\n\t-l: print lowercase\n\t--help: shows this help info\n");
    }
    else {
        printf("ERROR: unrecognized argument '%s'. Use --help to see all args.\n", arg);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void print_upper_char() {
    const int LOWER_BOUND = 65, UPPER_BOUND = 91;
    char c = (char) ((rand() % (UPPER_BOUND - LOWER_BOUND)) + LOWER_BOUND);
    printf("%c\n", c);
    return;
}

void print_lower_char() {
    const int LOWER_BOUND = 97, UPPER_BOUND = 123;
    char c = (char) ((rand() % (UPPER_BOUND - LOWER_BOUND)) + LOWER_BOUND);
    printf("%c\n", c);
    return;
}