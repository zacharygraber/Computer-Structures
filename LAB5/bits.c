/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Points: 5
 */
int bitAnd(int x, int y) {
  // Uses De Morgan's Law
  return ~(x | y);
}

/* 
 * getByte - Extract nth byte from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 10
 */
int getByte(int x, int n) {
  // Uses a mask to first clear all bits EXCEPT at byte n, then shifts n to the far "right" side
  // Abuses the fact that False∧x≡False and True∧x≡x
  int mask = 255; // So the mask is 00000000 00000000 00000000 11111111
  const int n_times_8 = n+n+n+n+n+n+n+n; // Get n*8 without using *
  mask = mask << n_times_8; // e.g. for n=2, mask is now 00000000 11111111 00000000 00000000
  int result = x & mask; // 0 out all other bits besides the ones in byte n
  return result >> n_times_8;
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Points: 10
 */
int byteSwap(int x, int n, int m) {
    // First use the same trick as in getByte() to store byte n in n_temp and m in m_temp
    // Then abuse the fact that False∧x≡False to clear bytes n and m
    // Then abuse the fact that 0⊕x=x to set bits
    
    // Store original byte at n
    int mask = 255;
    const int n_times_8 = n+n+n+n+n+n+n+n;
    mask = mask << n_times_8;
    int n_temp = (x & mask) >> n_times_8;

    // Store original byte at m
    mask = 255;
    const int m_times_8 = n+n+n+n+n+n+n+n;
    mask = mask << m_times_8;
    int m_temp = (x & mask) >> m_times_8;

    // Set all bits in bytes n to 0 then replace them with vals originally at m
    mask = 255; // Mask is 0x000000FF
    mask = mask << n_times_8; // For n=2, mask would now be 0x00FF0000
    x = x & mask; // Clears byte n
    n_temp = n_temp << m_times_8; // Shift it to the left to get it into byte m's position
    x = x ^ n_temp;

    // Do the same for m
    mask = 255;
    mask = mask << m_times_8;
    x = x & mask; // Clears byte m
    m_temp = m_temp << n_times_8;
    
    return x ^ m_temp;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 15
 */
int logicalShift(int x, int n) {
  return 2;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitCount(int x) {
  return 2;
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Points: 20
 */
int bang(int x) {
  return 2;
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitParity(int x) {
  return 2;
}
