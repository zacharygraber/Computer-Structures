/**************************************************************
 * Filename: twos_comp_part1.c                                *
 * Description: implements CSCI-H 335 Spring 2020 LAB6 Part1  *
 * Author: Zachary E Graber (zegraber@iu.edu)                 *
 * Date: 4/14/2021                                            *
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define BIT_DEPTH 8
#define MAX_VAL 127
#define MIN_VAL -128

void toBinaryString(int num, char* target); 

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR: Expected 1 positional argument:\n<number in decimal>\n");
		exit(EXIT_FAILURE);
	}
	int num = atoi(argv[1]);
	if (num > MAX_VAL || num < MIN_VAL) {
		printf("ERROR: Input %d exceeds expected range of 8 bits!\n", num);
		exit(EXIT_FAILURE);
	}
	
	char result[BIT_DEPTH + 1];

	// If the number is positive, then all we need to do is set the MSB
	if (num >= 0) {
		toBinaryString(num, result);
	}
	// It's easiest just to add a special case for this, since the method below won't work.
	else if (num == MIN_VAL) {
		result[0] = '1';
		int i;
		for (i = 1; i < BIT_DEPTH; i++) {
			result[i] = '0';
		}
		result[BIT_DEPTH] = '\0';
	}
	else {
		// Get the binary for the absolute value, negate it, then add 1
		toBinaryString(abs(num), result);
		int i;
		for (i = 0; i < BIT_DEPTH; i++) {
			result[i] = (result[i] == '1') ? '0' : '1';
		}
		// Goes from right to left in the binary number and flips the first 0 it sees to a 1, flipping 1s to 0s along the way
		for (i = BIT_DEPTH - 1; i >= 0; i--) {
			if (result[i] == '0') {
				result[i] = '1';
				break;
			}
			else {
				result[i] = '0';
			}
		}
	}
	printf("%s\n", result);
	exit(EXIT_SUCCESS);
}

// Only affects the last 7 bits (sets the MSB to 0 always). Only works for positive/0 values of num
void toBinaryString(int num, char* target) {
	// Make a C-string to hold our value
	char* result = target;
	result[BIT_DEPTH] = '\0';

	result[0] = '0';
	int i;
	for (i = BIT_DEPTH - 2; i >= 0; i--) { // Start by checking if greater than 2^6, then 2^5, and so on
		int bit_index = BIT_DEPTH - (i + 1); // The index in our result array (starts at 1, then 2, etc)
		int power_of_two = 1 << i; // 1 << i = 1*(2^i)
		if (num >= power_of_two) {
			result[bit_index] = '1';
			num -= power_of_two;
		}
		else {
			result[bit_index] = '0';
		}
	}
}
