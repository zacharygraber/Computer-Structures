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

typedef union {
    double result;
    struct {
        unsigned long mantissa : MANTISSA_SIZE;
        unsigned long exp : EXP_SIZE;
        int sign : 1;
    } parts;
} union_special_thing;

unsigned long binary_to_int(char* bin_num, int numbits);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect input argument\n");
        exit(EXIT_FAILURE);
    }
    char* input = argv[1];
    int i;
    // for (i = 0; i < BIT_DEPTH; i++) {
    //     if (input[i] != '1' || input[i] != '0') {
    //         printf("Incorrect input argument\n");
    //         exit(EXIT_FAILURE);
    //     }
    // }

    union_special_thing input_struct;
    printf("Sign: %c\n", input[0]);
    input_struct.parts.sign = input[0] == '1' ? 1 : 0;

    char exp[EXP_SIZE];
    strncpy(exp, input+1, EXP_SIZE);
    int e = binary_to_int(exp, BIT_DEPTH);
    input_struct.parts.exp = e;
    printf("Exponent: %u\n", e);

    char mantissa_string[MANTISSA_SIZE];
    strncpy(mantissa_string, input+1+EXP_SIZE, MANTISSA_SIZE);
    unsigned long mantissa = binary_to_int(mantissa_string, MANTISSA_SIZE);
    printf("Mantissa: %.17g\n", (double)mantissa);
    input_struct.parts.mantissa = mantissa;

    printf("Number: %.7g\n", input_struct.result);

    exit(EXIT_SUCCESS);
}

unsigned long binary_to_int(char* bin_num, int numbits) {
	unsigned long result = 0;
	int i;
	for (i = 0; i < numbits; i++) { // i is the index of the bit, with 0 being the MSB and BIT_DEPTH-1 the LSB
		unsigned long power_of_two = numbits - (i + 1); // The power of two scalar associated with this bit index
		if (bin_num[i] == '1') {
			result += (1 << power_of_two); // Left-shifting 1 by power_of_two is == to multiplying 1 by 2^(power_of_two)
		}
	}
	return result;
}