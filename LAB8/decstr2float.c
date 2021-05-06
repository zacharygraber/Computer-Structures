/**************************************************************
 * Filename: decstr2float.c                                   *
 * Description: implements CSCI-H 335 Spring 2020 LAB8 Part1  *
 * Author: Zachary E Graber (zegraber@iu.edu)                 *
 * Date: 5/5/2021                                             *
 **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT_DEPTH 32
#define EXP_SIZE 8
#define MANTISSA_SIZE 23
#define BIAS 127

int binary_to_int(char* bin_num);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect input argument\n");
        exit(EXIT_FAILURE);
    }
    char* input = argv[1];
    if (strlen(input) != BIT_DEPTH) {
        printf("Incorrect input argument\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < BIT_DEPTH; i++) {
        if (input[i] != '1' || input[i] != '0') {
            printf("Incorrect input argument\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Sign: %c\n", input[0]);

    exit(EXIT_SUCCESS);
}

int binary_to_int(char* bin_num) {
	int result = 0;
	int i;
	for (i = 0; i < BIT_DEPTH; i++) { // i is the index of the bit, with 0 being the MSB and BIT_DEPTH-1 the LSB
		unsigned long power_of_two = BIT_DEPTH - (i + 1); // The power of two scalar associated with this bit index
		if (bin_num[i] == '1') {
			result += (1 << power_of_two); // Left-shifting 1 by power_of_two is == to multiplying 1 by 2^(power_of_two)
		}
	}
	return result;
}