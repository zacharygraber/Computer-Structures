/**************************************************************
 * Filename: twos_comp_part2.c                                *
 * Description: implements CSCI-H 335 Spring 2020 LAB6 Part2  *
 * Author: Zachary E Graber (zegraber@iu.edu)                 *
 * Date: 4/14/2021                                            *
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT_DEPTH 8

int binary_to_int(char* bin_num);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("ERROR: Expected 2 positional arguments:\n<number in binary> <int type>\n");
		exit(EXIT_FAILURE);
	}
	char* bin_num = argv[1];
	if (strlen(bin_num) != BIT_DEPTH) {
		printf("ERROR: expected binary number [arg1] of 8 bits!\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[2], "signed") == 0) {
		if (bin_num[0] == '0') { // If the number is positive
			printf("%d\n", binary_to_int(bin_num));
		}
		else { // Negative numbers
			// Negate the binary number
			int i;
			for (i = 0; i < BIT_DEPTH; i++) {
				bin_num[i] = (bin_num[i] == '0') ? '1': '0';
			}
			
			// Convert to decimal
			int result = binary_to_int(bin_num);

			// Add one and reintroduce the negative sign
			result = (result + 1) * -1;
			printf("%d\n", result);
		}
	}
	else if (strcmp(argv[2], "unsigned") == 0) {
		printf("%d\n", binary_to_int(bin_num));
	}
	else {
		printf("ERROR: 2nd argument must be one of:\n\t>'signed'\n\t'unsigned'\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int binary_to_int(char* bin_num) {
	int result = 0;
	int i;
	for (i = 0; i < BIT_DEPTH; i++) { // i is the index of the bit, with 0 being the MSB and BIT_DEPTH-1 the LSB
		int power_of_two = BIT_DEPTH - (i + 1); // The power of two scalar associated with this bit index
		if (bin_num[i] == '1') {
			result += (1 << power_of_two); // Left-shifting 1 by power_of_two is == to multiplying 1 by 2^(power_of_two)
		}
	}
	return result;
}
