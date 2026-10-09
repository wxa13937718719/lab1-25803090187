/* 
 * CS:APP Data Lab 
 * 
 * name: 王兴安
 * Student ID: 25803090187
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* Move the bit in 1 to the most significant position. */
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* Find bits set in only one input, then combine them using De Morgan's law. */
	int onlyX = x & ~y;
  int onlyY = ~x & y;
  return ~(~onlyX & ~onlyY);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* Negate x and use its sign bits to keep the result only when x is negative. */
  return (~x + 1) & (x >> 31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* Extract the source byte, clear the destination, then insert the byte. */
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int srcByte = (x >> srcShift) & 0xFF;
  int dstMask = 0xFF << dstShift;
  return (x & ~dstMask) | (srcByte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* Clear the sign bits introduced by an arithmetic right shift. */
  int shifted = x >> n;
  int sign = 1 << 31;
  int unwanted = (sign >> n) << 1;
  int keep = ~unwanted;
  return shifted & keep;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* Move each low nibble up and each high nibble down within its byte. */
  int lowMask = 0x0F | (0x0F << 8);
  lowMask = lowMask | (lowMask << 16);
  int lowToHigh = (x & lowMask) << 4;
  int highToLow = (x >> 4) & lowMask;
  return lowToHigh | highToLow;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* Set the lowest zero bit, then isolate the next lowest zero bit. */
  int y = x | (x + 1);
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* Fold the parity of all 32 bits into bit 0, then invert it. */
  int p = x;
  p = p ^ (p >> 16);
  p = p ^ (p >> 8);
  p = p ^ (p >> 4);
  p = p ^ (p >> 2);
  p = p ^ (p >> 1);
  return !(p & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* Move the low bits to the top and clear sign bits from the right shift. */
  int k = n & 31;
  int right = x >> k;
  int unwanted = ((1 << 31) >> k) << 1;
  int leftShift = (32 + (~k + 1)) & 31;
  int wrapped = x << leftShift;
  return (right & ~unwanted) | wrapped;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* Add a tie-aware bias, then discard the low n bits to round. */
  int half = (1 << n) >> 1;
  int q = x >> n;
  int bias = (half + ~0) + (q & 1);
  return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* Compute the floor midpoint safely, then round halfway cases toward x. */
  int mid = (x & y) + ((x ^ y) >> 1);

    int d = (x >> 1) + ~(y >> 1) + 1;

    int up = ((x ^ y) & 1)
           & !(d >> 31)
           & (!!d | (x & 1));

    return mid + up;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* Compare x with both endpoints using sign-aware masks, including equality. */
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;

  int da = x + ~a + 1;
  int db = x + ~b + 1;

  int ma = sx ^ sa;
  int mb = sx ^ sb;

  int gea = (ma & ~sx) | (~ma & ~(da >> 31));
  int geb = (mb & ~sx) | (~mb & ~(db >> 31));

  return !!((gea ^ geb) | !(x ^ a) | !(x ^ b));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x4 = x << 2;
  int result = x4 + x;

  // 检查左移两位是否溢出
  int overflow1 = !!((x >> 29) ^ (x >> 31));

  // 检查最终结果是否与 x 符号不同
  int overflow2 = ((x ^ result) >> 31) & 1;

  // 是否发生溢出
  int overflow = overflow1 | overflow2;

  // 溢出掩码：0 或 0xFFFFFFFF
  int mask = ~overflow + 1;

  // x >= 0 时为 INT_MAX，否则为 INT_MIN
  int sat = ~(1 << 31) ^ (x >> 31);

  // 根据是否溢出选择结果
  return (result & ~mask) | (sat & mask);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 分别记录两次加法的溢出方向；相反方向的溢出会抵消。 */
    int sumXY = x + y;
    int sum = sumXY + z;

    int sx = x >> 31;
    int sy = y >> 31;
    int sxy = sumXY >> 31;
    int sz = z >> 31;
    int ssum = sum >> 31;

    int pos1 = (~sx & ~sy & sxy) & 1;
    int neg1 = (sx & sy & ~sxy) & 1;

    int pos2 = (~sxy & ~sz & ssum) & 1;
    int neg2 = (sxy & sz & ~ssum) & 1;

    return (pos1 + pos2) + ~(neg1 + neg2) + 1;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    /* 拆出符号、指数和小数部分，再对有效数字乘 3/2 并就近舍入。 */
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xffu;
    unsigned frac = uf & 0x7fffffu;

    if (exp == 0xffu) {
        return uf;  /* NaN 和无穷大 */
    }

    unsigned mant = frac;
    if (exp != 0) {
        mant |= 0x800000u;  /* 普通数补上隐藏的最高位 1 */
    }

    unsigned triple = mant * 3u;
    unsigned shift = 1u;
    if (exp != 0 && triple >= 0x2000000u) {
        shift = 2u;
        exp++;
    }

    unsigned q = triple >> shift;
    unsigned lost = triple & ((1u << shift) - 1u);
    unsigned half = 1u << (shift - 1u);

    if (lost > half || (lost == half && (q & 1u))) {
        q++;
    }

    if (exp == 0) {
        return sign | q;
    }
    if (exp >= 0xffu) {
        return sign | 0x7f800000u;  /* 结果溢出为无穷大 */
    }
    return sign | (exp << 23) | (q & 0x7fffffu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    /* 按最近整数舍入；恰好一半时选偶数，并保留零的符号。 */
    unsigned sign = uf & 0x80000000u;
    unsigned exp = (uf >> 23) & 0xffu;
    unsigned frac = uf & 0x7fffffu;

    if (exp == 0xffu) {
        return uf;  /* NaN 或无穷大 */
    }

    if (exp < 126u) {
        return sign;  /* 绝对值小于 0.5 */
    }

    if (exp == 126u) {
        if (frac == 0u) {
            return sign;  /* 恰好是 ±0.5，取偶数 0 */
        }
        return sign | 0x3f800000u;  /* 绝对值大于 0.5、小于 1 */
    }

    if (exp >= 150u) {
        return uf;  /* 编码中已经没有小数位 */
    }

    unsigned n = 150u - exp;
    unsigned mask = (1u << n) - 1u;
    unsigned remainder = frac & mask;
    unsigned truncated = uf & ~mask;
    unsigned half = 1u << (n - 1u);
    unsigned mant = 0x800000u | frac;

    if (remainder > half ||
        (remainder == half && ((mant >> n) & 1u))) {
        truncated += 1u << n;
    }

    return truncated;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    /* 将整数对齐到浮点有效数字；丢位时按最近偶数舍入。 */
    unsigned sign = 0u;
    unsigned mag = x;
    int top = 31;
    unsigned exp;
    unsigned mant;
    unsigned shift;
    unsigned lost;
    unsigned half;

    if (x == 0) {
        return 0u;
    }

    if (x < 0) {
        sign = 0x80000000u;
        mag = 0u - mag;
    }

    while ((mag >> top) == 0u) {
        top--;
    }

    exp = top + 127u;

    if (top <= 23) {
        mant = mag << (23 - top);
    } else {
        shift = top - 23;
        mant = mag >> shift;
        lost = mag & ((1u << shift) - 1u);
        half = 1u << (shift - 1u);

        if (lost > half ||
            (lost == half && (mant & 1u))) {
            mant++;
        }

        if (mant == (1u << 24)) {
            mant >>= 1;
            exp++;
        }
    }

    return sign | (exp << 23) | (mant & 0x7fffffu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
    /* 先分别统计每 2 位、4 位、8 位中的 1，再合并四个字节。 */
    int m1 = 0x55 | (0x55 << 8);
    int m2 = 0x33 | (0x33 << 8);
    int m4 = 0x0F | (0x0F << 8);

    m1 = m1 | (m1 << 16);
    m2 = m2 | (m2 << 16);
    m4 = m4 | (m4 << 16);

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);

    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {
    /* 依次交换 16 位、8 位、4 位、2 位和 1 位的小组。 */
    int mask = 0xFF | (0xFF << 8);  /* 0x0000FFFF */

    x = ((x >> 16) & mask) | (x << 16);

    mask = mask ^ (mask << 8);      /* 0x00FF00FF */
    x = ((x >> 8) & mask) | ((x & mask) << 8);

    mask = mask ^ (mask << 4);      /* 0x0F0F0F0F */
    x = ((x >> 4) & mask) | ((x & mask) << 4);

    mask = mask ^ (mask << 2);      /* 0x33333333 */
    x = ((x >> 2) & mask) | ((x & mask) << 2);

    mask = mask ^ (mask << 1);      /* 0x55555555 */
    x = ((x >> 1) & mask) | ((x & mask) << 1);

    return x;
}
