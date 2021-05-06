/**************************************************************
 * Filename: float2bitstr.c                                   *
 * Description: implements CSCI-H 335 Spring 2020 LAB8 Part2  *
 * Author: Zachary E Graber (zegraber@iu.edu)                 *
 * Date: 5/5/2021                                             *
 **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BIT_DEPTH 32
#define EXP_SIZE 8
#define MANTISSA_SIZE 23
#define BIAS 127

void toBinaryString(int num, int numbits, char* target);
void toBinaryStringUnsigned(int num, int numbits, char* target);
void toBinaryStringFractional(double num, int numbits, char* target);
double pow2Negative(int exponent);

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
        double power_of_two = pow2Negative((i+1));
        if (num >= power_of_two) {
            result[i] = '1';
            num -= power_of_two;
        }
        else {
            result[i] = '0';
        }
    }
}

double pow2Negative(int exponent) {
	double answers[] = {1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125, 0.00390625, 0.001953125, 0.0009765625, 0.00048828125, 0.000244140625, 0.0001220703125, 6.103515625e-05, 3.0517578125e-05, 1.52587890625e-05, 7.62939453125e-06, 3.814697265625e-06, 1.9073486328125e-06, 9.5367431640625e-07, 4.76837158203125e-07, 2.384185791015625e-07, 1.1920928955078125e-07, 5.960464477539063e-08, 2.9802322387695312e-08, 1.4901161193847656e-08, 7.450580596923828e-09, 3.725290298461914e-09, 1.862645149230957e-09, 9.313225746154785e-10, 4.656612873077393e-10, 2.3283064365386963e-10, 1.1641532182693481e-10, 5.820766091346741e-11, 2.9103830456733704e-11, 1.4551915228366852e-11, 7.275957614183426e-12, 3.637978807091713e-12, 1.8189894035458565e-12, 9.094947017729282e-13, 4.547473508864641e-13, 2.2737367544323206e-13, 1.1368683772161603e-13, 5.684341886080802e-14, 2.842170943040401e-14, 1.4210854715202004e-14, 7.105427357601002e-15, 3.552713678800501e-15, 1.7763568394002505e-15, 8.881784197001252e-16, 4.440892098500626e-16, 2.220446049250313e-16, 1.1102230246251565e-16, 5.551115123125783e-17, 2.7755575615628914e-17, 1.3877787807814457e-17, 6.938893903907228e-18, 3.469446951953614e-18, 1.734723475976807e-18, 8.673617379884035e-19, 4.336808689942018e-19, 2.168404344971009e-19, 1.0842021724855044e-19};
	return answers[exponent];
}
