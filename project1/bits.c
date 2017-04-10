/* 
 *Lab of Computer Architecture 
 * 
 * <Please put your name and userid here>
 * liangmingyu 515010910101
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
//it's very easy x&y=~(~x|~y)
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return (x>>(n<<3) & 0xff);
}
//1 bite=8 bits=2^3 bits
//first move the byte we want to the low position and by & 0xff to select it out
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int t=(1<<31)&x;
  t=~((t>>n)<<1);
  x=x>>n;
  return x&t;
}
//get its sign bit
//after arithmetic shift we need to make the bits before sign bit all 0
//use the sign bit shift right n-1 then we get n bits sign bits get their ~ and & with the result from step2 we can achieve the funct
//note that n might be 0 so we can't directly shift right n-1
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int tmp=(((0x01<<8 | 0x01)<<8 | 0x01)<<8 | 0x01)<<8 | 0x01;
  int val=tmp&x;         //0,8,16,24
  val+=tmp&(x>>1);      // 1,9,17,25
  val+=tmp&(x>>2);        
  val+=tmp&(x>>3);
  val+=tmp&(x>>4);
  val+=tmp&(x>>5);
  val+=tmp&(x>>6);
  val+=tmp&(x>>7);         //7,15,23,32
  val+=(val>>16);
  val+=(val>>8);
  return val&0xff;
}
//under the restriction of the ops, we need to detect several bits at the same time and 4 is a choice (make up easily and enough)
//make up 00000001000000010000000100000001
//use these ops to calculate the number of 1
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int t=(x |(~x+1))>>31;
  return (~t)&0x01;
}
//get q=~x+1 the difference between 0 and others is that for 0 q and x 's sign bits are all 0, but if x!=0 x,q exist one 1 sign bit
//get | of x and q's sign bit, 0 is 0 and others' is 1
//then we can ~q and & with 0x01
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1<<31;
}
//maybe quite easy
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  n=(x>>(n+~1+1));
  return (!n)^!(~n);
}
//bits before n and n must be all 0 or 1, 0000..000 or 111.11111
//!n=1 , !(~n)=1 only one exist,so we use ^
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int s=!!(x>>31);
  int t=(1<<n)+~0;
  int low=t&x;
  return (x>>n)+((!!low)&s);
}
//x/(2^n)=~((~x+1)>>n)+1
//refer to the formula from the website, know that 
//if after n bits all 0 ~x+1 's n+1~32bits same as ~x+(1<<n)
//so ~((~x+1)>>n)+1=~((~x>>n)+1)+1=x>>n
//if after n bits not all 0 ~x+1 and ~x same n+1~32
//so ~((~x+1)>>n)+1=~((~x)>>n)+1=x>>n+1
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
//maybe quite easy
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  int s=!(x>>31);
  return s&!!x;
}
//get sign bit if x>0 s=1 !!x=1 if x<0 s=0 !!x=1
//note that x=0 return 0 so s&!!x
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int xx=!!(x>>31);
  int yy=!!(y>>31);
  int z=y+(~x+1);
  int s=!(z>>31);	
  return ((!(xx^yy))&s)|((xx^yy)&(!yy));
}
//get x,y's sign bit xx,yy
//if x<=y then y-x>=0 
//if x,y same sign, xx^yy=0 ,no overflow ,judge sign bit of y-x
//if xx^yy=1, result's sign must equal to y's ,so (xx^yy)&(!yy)
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int s,s1,s2,s3,s4,s5;
  s=!!(x>>16);   //judge if is at 16-31?
  s1=s<<4;        //if is ,shift to judge 16-31,or judge 0-15
  x>>=s1;
  s=!!(x>>8);
  s2=s<<3;
  x>>=s2;
  s=!!(x>>4);
  s3=s<<2;
  x>>=s3;
  s=!!(x>>2);
  s4=s<<1;
  x>>=s4;
  s=!!(x>>1);
  s5=s;
  return s1+s2+s3+s4+s5;
}
//use bisection method
//if left has 1,then abandon right and analyse left, or analyse right
//use s1,s2...to record the location information
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  unsigned exp=uf<<1>>24;      //get exp if uf>>23 the sign bit will effect the judgement after
  unsigned frac=uf & 0x7FFFFF;   //get frac
  if((exp==0xFF) && frac)   //judge is NaN ,if is ,exp==0xFF and frac!=0
    return uf;                 //is NaN,return itself
  else 
    return uf^0x80000000;       //else ~ sign bit 
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned shiftleft=0;    
  unsigned aftershift=x,tmp,flag;
  unsigned sign=x>>31<<31;     //logical shift
  if(x==0) return 0;
  if(x<0) 
    aftershift=-x;             //aftershift origin is abs(x) because only sign bit changes
  while(1)
  {
    tmp=aftershift;
    aftershift<<=1;             //shift left until 31st bit=1
    shiftleft++;                 //record the times of shift left to calculate e
    if(tmp & 0x80000000) break;  //judgement 
  }
  if((aftershift & 0x01ff)>0x0100)   //larger than 5, add 1
      flag=1;
  else if((aftershift & 0x03ff)==0x0300)   //equal to 5, if frac's last bit is 0, add 0, else, add 1
      flag=1;
  else 
      flag=0;
  return sign+(aftershift>>9)+((159-shiftleft)<<23)+flag;   //according to the formula, if leftest 1 is x1 bit, E-127=x1+1=31-shiftleft+1
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned exp=uf<<1>>24;
  if(exp==0)
  {
    uf=((uf & 0x007FFFFF)<<1) | (0x80000000 & uf); //sign bit:0x80000000 & uf, 
  }
  else if(exp!=0xff)
  {
    uf+=0x00800000;
  }
  return uf;
}
//if uf's exp all 0, non-normalized number, only need to shift 1 left to frac
//if uf's exp not all 0 or all 1, normalized number, exp+1
//else directly return the value


