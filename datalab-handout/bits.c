/* 
 * CS:APP Data Lab 
 * 
 * <Lee>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */

int bitXor(int x, int y) {
/* 
** A NAND B = ~(A & B)
** [ A NAND ( A NAND B ) ] NAND
** [ B NAND ( A NAND B ) ]
** 모든 게이트는 NAND게이트로 만들 수 있다.
*/
  return ~( ~( x & ~( x & y ) ) &
            ~( y & ~( x & y ) ) );
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*
** 최소값은 0x80000000
*/
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/*
** exp1: ~((x+1) ^ x) = 0 (when either MAX or -1)
**
** exp2: !(x+1)
** (case x=-1) 	=>	1
** (case x=MAX)	=>	0
** 
** if exp1 and exp2 are all zero
** then x is the maximum
*/
  return !(~((x+1) ^ x) | !(x+1));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
/*
** complete_odd_nbit: all add-numbered bits in n-bits to 1 and even-numbered bits in n-bits set to 0
** x & complete_odd_32bit => if x is allOddBits then (x & complete_odd_32bit) is complete_odd_32bit
** !(a ^ b) is a == b
*/
  const int complete_odd_8bit = 0xAA;
  const int complete_odd_16bit = complete_odd_8bit | (complete_odd_8bit << 8);
  const int complete_odd_32bit = complete_odd_16bit | (complete_odd_16bit << 16);

  return !((x & complete_odd_32bit) ^ complete_odd_32bit);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/*
** ~x + 1 is -x
*/
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
/*
** x_bigger_than_lower_bound: x >= lower_bound
** x_smaller_than_upper_bound: upper_bound >= x
** principle:
** 1. a - b = a + (~b + 1)
** 2. (msb of a) => (a >> 31) so, if (a < 0) then (msb = 1) else (msb = 0)
*/
  const int lower_bound = 0x30;
  const int upper_bound = 0x39;
  const int x_bigger_than_lower_bound = !((x + (~lower_bound + 1)) >> 31);
  const int x_smaller_than_upper_bound = !((upper_bound + (~x + 1)) >> 31);
  return x_bigger_than_lower_bound & x_smaller_than_upper_bound;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
/*
** binarized_x: all bits are negative if x == 0 else (all bits are positive)
** if all bits of the x are positive then x & operand = operand
*/
  const int binarized_x = ~(!!x) + 1;
  
  return (binarized_x & y) | (~binarized_x & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*
** x   y   rst
** +   +   !(x - y)
** +   -   sign of y
** -   +   sign of y
** -   -   !(x - y)
** Overflow does not occur because x and y have the same sign when calculating their difference
** if x == y then 1
**
** binarized_diff_msb: -1 if msb is different else 0
** positivity_y: 1 if y >= 0 else 0
** positivity_gap: 1 if x-y >= 0 else 0
** (binarized_diff_msb ? positivity_y : !positivity_gap) or x == y
*/
  const int diff_msb  = (x >> 31) ^ (y >> 31);
  const int binarized_diff_msb = ~(!! diff_msb) + 1;
  const int positivity_y = !(y >> 31);
  const int positivity_gap = !((x + ~y + 1) >> 31);
  return ((binarized_diff_msb & positivity_y) | (~binarized_diff_msb & !positivity_gap) | !(x ^ y));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
/*
** 0 and -0 is same
** a and -a is different (a != 0)
** a >> 31, -a >> 31 : 둘중 하나는 모든 비트가 1, 나머지는 모든 비트가 0
*/
  const int negative_x = (~x + 1);
  const int shifed_x = x >> 31;
  const int shifed_negative_x = negative_x >> 31;
  return (shifed_x | shifed_negative_x) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int bitmask= ~!!(x >> 31) + 1;
  int positive_x = x ^ bitmask;
  //zero and -1 don't have msb
  //so, if x is -1 or zero cnt plus one
  int cnt = !!(positive_x ^ 0);
  int binarized_bit = 0;
  int exist_upper_bit = 0;
  int i = 0;

  //help for cut the lower bound
  bitmask = ~(1 << 31);

  //Binary search
  i = 16;
  bitmask = bitmask >> 15;
  exist_upper_bit = !!(positive_x >> i);
  cnt = cnt + (exist_upper_bit << 4);
  binarized_bit = ~exist_upper_bit+1;
  positive_x = (binarized_bit & (positive_x >> i)) | (~binarized_bit & positive_x & bitmask);
  
  i = 8;
  bitmask = bitmask >> i;
  exist_upper_bit = !!(positive_x >> i);
  cnt = cnt + (exist_upper_bit << 3);
  binarized_bit = ~exist_upper_bit+1;
  positive_x = (binarized_bit & (positive_x >> i)) | (~binarized_bit & positive_x & bitmask);

  i = 4;
  bitmask = bitmask >> i;
  exist_upper_bit = !!(positive_x >> i);
  cnt = cnt + (exist_upper_bit << 2);
  binarized_bit = ~exist_upper_bit+1;
  positive_x = (binarized_bit & (positive_x >> i)) | (~binarized_bit & positive_x & bitmask);

  i = 2;
  bitmask = bitmask >> i;
  exist_upper_bit = !!(positive_x >> i);
  cnt = cnt + (exist_upper_bit << 1);
  binarized_bit = ~exist_upper_bit+1;
  positive_x = (binarized_bit & (positive_x >> i)) | (~binarized_bit & positive_x & bitmask);

  i = 1;
  bitmask = bitmask >> i;
  exist_upper_bit = !!(positive_x >> i);
  cnt = cnt + exist_upper_bit;
  binarized_bit = ~exist_upper_bit+1;
  positive_x = (binarized_bit & (positive_x >> i)) | (~binarized_bit & positive_x & bitmask);

  return cnt+1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {\
  const unsigned s_bitmask = 0x80000000u;
  const unsigned exp_bitmask = 0x7f800000u;
  const unsigned exp_alpha = 0x00800000u;
  const unsigned frac_bitmask = 0x007fffffu;

  unsigned s = uf & s_bitmask;
  unsigned exp = uf & exp_bitmask;
  unsigned frac = uf & frac_bitmask;

  //special values
  if (!(exp ^ exp_bitmask)) return uf;

  //denormalized values
  if (!exp)
    return s | exp | (frac << 1);

  //normal values
  return s | (exp + exp_alpha) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  const unsigned s_bitmask = 0x80000000u;
  const unsigned exp_bitmask = 0x7f800000u;
  const unsigned special_values = 0x80000000u;
  
  int pow_2_E = 0;
  int i = 0;

  unsigned s = uf & s_bitmask;
  unsigned exp = uf & exp_bitmask;

  //special values
  if (!(exp ^ exp_bitmask)) return special_values;

  //denormalized vlaues
  if (!exp)
    return 0;

  //normal vlaues
  pow_2_E = 1;
  i = (exp >> 23) - 127;
  if (i < 0)
    return 0;
  if (i > 31)
    return special_values;

  while (i-- > 0)
    pow_2_E = pow_2_E << 2;
  s = s ? -1 : 1;
  return s * pow_2_E;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  const int positive_INF = 0x7f800000u;
  const int negative_INF = 0;
  const unsigned exp = (x + 127) << 23;

  if (x < -126)
    return negative_INF;
  if (x > 128)
    return positive_INF;
  
  return exp ;
}
