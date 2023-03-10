/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Points: 5
 */
int bitAnd(int x, int y) {
  // Uses De Morgan's Law
  return ~((~x) | (~y));
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
  unsigned int result;
  const int n_times_8 = n << 3; // Get n*8 without using *
  mask = mask << n_times_8; // e.g. for n=2, mask is now 00000000 11111111 00000000 00000000
  result = x & mask; // 0 out all other bits besides the ones in byte n
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
    
    unsigned int n_temp;
    unsigned int m_temp;
    int n_times_8;
    int m_times_8;
    // Store original byte at n
    int mask = 255;
    n_times_8 = n << 3;
    mask = mask << n_times_8;
    n_temp = x & mask;
    n_temp = n_temp >> n_times_8;

    // Store original byte at m
    mask = 255;
    m_times_8 = m << 3;
    mask = mask << m_times_8;
    m_temp = x & mask;
    m_temp = m_temp >> m_times_8;

    // Set all bits in bytes n to 0 then replace them with vals originally at m
    mask = 255; // Mask is 0x000000FF
    mask = mask << n_times_8; // For n=2, mask would now be 0x00FF0000
    mask = ~mask;
    x = x & mask; // Clears byte n
    m_temp = m_temp << n_times_8; // Shift it to the left to get it into byte m's position
    x = x ^ m_temp;

    // Do the same for m
    mask = 255;
    mask = mask << m_times_8;
    mask = ~mask;
    x = x & mask; // Clears byte m
    n_temp = n_temp << m_times_8;
    
    return x ^ n_temp;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 15
 */
int logicalShift(int x, int n) {
  // First do an arithmetic shift by n
  // We then make a mask of all 1s (-1 decimal) and << by 32-n to get 1s in the right place
  // Then negate the mask to take advantage of x&0=0 and x&1=x to get rid of leading 1s, but preserve data
  int mask;
  mask = -1;
  mask = ~(mask << (32 - n));
  printf("%d\n", mask);
  return (x >> n) & mask;
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
  return ~(x & 1);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitParity(int x) {
  // Recursively exploit ^ to find if an odd number of 1s are present
  unsigned int temp; // We need logical shifts
  temp = x ^ (x >> 1);
  temp ^= temp >> 2;
  temp ^= temp >> 4;
  temp ^= temp >> 8;
  temp ^= temp >> 16;
  return temp & 1;
}
