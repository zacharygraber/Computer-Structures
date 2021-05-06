/**************************************************************
 * Filename: float2bitstr.c                                   *
 * Description: implements CSCI-H 335 Spring 2020 LAB8 Part2  *
 * Author: Zachary E Graber (zegraber@iu.edu)                 *
 * Date: 5/5/2021                                             *
 **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BIT_DEPTH 32
#define EXP_SIZE 8
#define MANTISSA_SIZE 23
#define BIAS 127

void toBinaryString(int num, int numbits, char* target);
void toBinaryStringUnsigned(int num, int numbits, char* target);
void toBinaryStringFractional(double num, int numbits, char* target);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("No input given\n");
        exit(EXIT_FAILURE);
    }
    double input = atof(argv[1]);
    // Edge case
    if (input == 0) {
        printf("00000000000000000000000000000000\n");
        exit(EXIT_SUCCESS);
    }

    // Calculate the exponent. We first need the integer part in binary...
    char integer_part[BIT_DEPTH + 1]; // Stores the int. part in binary
    toBinaryStringUnsigned(abs((int) input), BIT_DEPTH, integer_part);
    char fractional_part[126 + 23 + 1]; // If the exponent is 2^(-126) then we'll need 23 more bits for the mantissa
    //printf("\n%f\n", abs(input) - (float)((int)abs(input)));
    toBinaryStringFractional(fabs(input - (int)(input)), 126+23, fractional_part);
    int exp, i;
    if (abs(input) < 1) { // Case when exponent is negative 
        // Go left to right until we encounter a 1
        exp = 0;
        for (i = 0; i < 126+23; i++) {
            exp--;
            if (fractional_part[i] == '1') {
                break;
            }
        }
    }
    else {
        for (i = 0; i < BIT_DEPTH; i++) {
            // Go left to right (MSB->LSB) until we encounter our implicit 1
            if (integer_part[i] == '1') {
                exp = BIT_DEPTH - (i + 1);
                break;
            }
        }
    }

    // Now that we have the exponent, we can worry about the rest
    char result[BIT_DEPTH + 1];
    result[BIT_DEPTH] = '\0';

    // Sign bit
    result[0] = input < 0 ? '1' : '0';

    // Exponent
    char exponent_binary[EXP_SIZE + 1];
    toBinaryStringUnsigned(exp + BIAS, EXP_SIZE, exponent_binary);
    for (i = 0; i < EXP_SIZE; i++) {
        result[i+1] = exponent_binary[i];
    }

    // Mantissa
    int mantissa_bits_written = 0;
    for (i = exp; i > 0; i--) {
        if (mantissa_bits_written == MANTISSA_SIZE) {
            break;
        }
        else {
            result[mantissa_bits_written+EXP_SIZE+1] = integer_part[BIT_DEPTH - i];
            mantissa_bits_written++;
        }
    }
    while (!(mantissa_bits_written == MANTISSA_SIZE)) {
        result[mantissa_bits_written+EXP_SIZE+1] = fractional_part[abs(i)];
	i--;
        mantissa_bits_written++;
    }

    //printf("Input: %f\nInteger: %s\nFraction: %s\nExp: %d\n\n", input, integer_part, fractional_part, exp);

    printf("%s\n", result);

    exit(EXIT_SUCCESS);
}

// Converts a natural number to its binary representation
void toBinaryString(int num, int numbits, char* target) {
	// Make a C-string to hold our value
	char* result = target;
	result[numbits] = '\0';

	result[0] = '0';
	int i;
	for (i = numbits - 2; i >= 0; i--) { // Start by checking if greater than 2^6, then 2^5, and so on
		int bit_index = numbits - (i + 1); // The index in our result array (starts at 1, then 2, etc)
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

// Converts a natural number to its binary representation
void toBinaryStringUnsigned(int num, int numbits, char* target) {
	// Make a C-string to hold our value
	char* result = target;
	result[numbits] = '\0';

	int i;
	for (i = numbits - 1; i >= 0; i--) { // Start by checking if greater than 2^6, then 2^5, and so on
		int bit_index = numbits - (i + 1); // The index in our result array (starts at 1, then 2, etc)
		unsigned long power_of_two = 1 << i; // 1 << i = 1*(2^i)
		if ((unsigned)num >= power_of_two) {
			result[bit_index] = '1';
			num -= power_of_two;
		}
		else {
			result[bit_index] = '0';
		}
		//printf("bit_index: %d");
	}
}

// Converts fractional part of the num to binary
void toBinaryStringFractional(double num, int numbits, char* target) {
    //printf("num: %f\n", num);
    // Make a C-string to hold our value
	char* result = target;
	result[numbits] = '\0';

    int i;
    // Go from left to right, starting at 1/2, then 1/4, then 1/8 and so on
    for (i = 0; i < numbits; i++) {
        double power_of_two = pow(2, -1* (i+1));
        if (num >= power_of_two) {
            result[i] = '1';
            num -= power_of_two;
        }
        else {
            result[i] = '0';
        }
    }
}
