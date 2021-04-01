#include "bitops.h"

/*
 * Return and of x and y
 * Points: 5
 */
int and_op(int x, int y) {
  // Just a simple usage of &
  return x & y;
}

/* 
 * Return or of x and y
 * Points: 5
 */
int or_op(int x, int y) {
  // A simple usage of |
  return x | y;
}

/*
 * Return xor of x and y
 * Points: 5
 */
int xor_op(int x, int y) {
  // More fun than just using ^
  // Uses logical equivalency X⊕Y≡(¬X∧Y)∨(X∧¬Y)
  return ((~x) & y) | (x & (~y));
}


/*
 * Extract `b`th byte of x
 * Points: 10
 */
int masking_and(int x, int b) {
  // x looks something like this: xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
  // define constant mask as:     00000000 00000000 00000000 11111111
  // shift mask left by b bytes (b*8 bits). 
  // 	example when b=2:         00000000 11111111 00000000 00000000
  // negate the mask:             11111111 00000000 11111111 11111111
  // True ∧ x ≡ x
  // False ∧ x ≡ False
  // So bitwise ∧ gives us        xxxxxxxx 00000000 xxxxxxxx 00000000
  // And we have cleared the bth byte of x
  int mask = 255; // in binary: 00000000 00000000 00000000 11111111
  const int b_times_8 = b + b + b + b + b + b + b + b; // Get b*8 without using multiplication operator
  mask = mask << b_times_8;
  mask = ~mask;
  return x & mask;
}

/*
 * Set `b`th byte of x
 * Points: 10
 */
int masking_or(int x, int b) {
  // Same as masking_and, but instead of mask & x, we do mask | x. Also, don't negate the mask
  // The mask for b=2, for example, is: 00000000 11111111 00000000 00000000
  // Exploits the facts that True ∨ x ≡ True, and False ∨ x ≡ x
  int mask = 255;
  const int b_times_8 = b + b + b + b + b + b + b + b;
  mask = mask << b_times_8;
  return x | mask;
}

/*
 * Toggle `b`th byte of x
 * Points: 10
 */
int masking_xor(int x, int b) {
  // Similar to masking_and and masking_or
  // Absuses the facts that True ⊕ x ≡ ¬x, and False ⊕ x ≡ x.
  // Example mask for b=2: 00000000 11111111 00000000 00000000
  int mask = 255;
  const int b_times_8 = b + b + b + b + b + b + b + b;
  mask = mask << b_times_8;
  return x ^ mask;
}

/*
 * Shift x to the left by `sc` # of bits
 * Points: 5
 */
int shifting_left_op(int x, int sc) {
  // literal use of <<
  return x << sc;
}

/*
 * Shift x to the right by `sc` # of bits
 * Points: 5
 */
int shifting_right_op(int x, int sc) {
  // literal use of >>
  return x >> sc;
}


/*
 * Return logical not of x
 * Points: 5
 */
int bang(int x) {
  return ~x;
}

/*
 * Print binary string representation for x
 * Points: 40
 */
void bit_conversion(int x) {
  // Checks each binary digit by using a mask for each bit
  // Abuses the fact that x∧True is x, and x∧False is False.
  // Also abuses the in C any non-zero int is True.
  int mask = 1; // Mask is 00000000 00000000 00000000 00000001
  int num_of_trues = 0;
  int i;
  for (i = 31; i >= 0; i--) {
    if (x & (mask << i)) {
	printf("1");
	num_of_trues += 1;
    }
    // Prevents leading 0s
    else if (num_of_trues) {
	printf("0");
    }
  }
}
