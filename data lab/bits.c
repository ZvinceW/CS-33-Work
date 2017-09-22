/*
* CS:APP Data Lab
*
* <Vince Wu   304805121>
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

INTEGER CODING RULES :

Replace the "return" statement in each function with one
or more lines of C code that implements the function.Your code
must conform to the following style :

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

Each "Expr" is an expression using ONLY the following :
1. Integer constants 0 through 255 (0xFF), inclusive.You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables(no global variables).
3. Unary integer operations !~
4. Binary integer operations & ^ | +<< >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators.You are not restricted to
one operator per line.

You are expressly forbidden to :
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, || , -, or ? :
	6. Use any form of casting.
	7. Use any data type other than int.This implies that you
	cannot use arrays, structs, or unions.


	You may assume that your machine :
1. Uses 2s complement, 32 - bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE :
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

For the problems that require you to implent floating - point operations,
the coding rules are less strict.You are allowed to use looping and
conditional control.You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to :
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc(data lab checker) compiler(described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators(!~& ^ | +<< >> )
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc.Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function.If there are any inconsistencies
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
* bang - Compute !x without using !
*   Examples: bang(3) = 0, bang(0) = 1
*   Legal ops: ~ & ^ | + << >>
*   Max ops: 12
*   Rating: 4
*/
int bang(int x) {
	/*
	If any 1-bit exists, keep spreading 1-bits towards the most significant bit until the most significant bit is a 1-bit,
	then arithmatically right shift 31 bits, the result would be -1 if 1-bit exists or 0 if 1-bit doesnt exist,
	return ~result & 1.
	*/
	int first;
	int second;
	int third;
	int fourth;
	int fifth;
	first = x >> 1;
	x = x | first;
	second = x >> 2;
	x = x | second;
	third = x >> 4;
	x = x | third;
	fourth = x >> 8;
	x = x | fourth;
	fifth = x >> 16;
	x = x | fifth;
	return ~x & 1;
}
/*
* bitCount - returns count of number of 1's in word
*   Examples: bitCount(5) = 2, bitCount(7) = 3
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 40
*   Rating: 4
*/
int bitCount(int x) {
	/*i implemented wikipedia's Hamming Weight algorithm*/
	int mask1, mask2, mask4, mask8, mask16;
	mask1 = 85;
	mask1 = mask1 | (mask1 << 8);
	mask1 = mask1 | (mask1 << 16);
	mask2 = 51;
	mask2 = mask2 | (mask2 << 8);
	mask2 = mask2 | (mask2 << 16);
	mask4 = 15;
	mask4 = mask4 | (mask4 << 8);
	mask4 = mask4 | (mask4 << 16);
	mask8 = 255;
	mask8 = mask8 << 16;
	mask8 = mask8 | 255;
	mask16 = 255 << 8;
	mask16 = mask16 | 255;
	x = (x & mask1) + ((x >> 1) & mask1); //put count of each  2 bits into those  2 bits 
	x = (x & mask2) + ((x >> 2) & mask2); //put count of each  4 bits into those  4 bits 
	x = (x & mask4) + ((x >> 4) & mask4); //put count of each  8 bits into those  8 bits 
	x = (x & mask8) + ((x >> 8) & mask8); //put count of each 16 bits into those 16 bits 
	x = (x & mask16) + ((x >> 16) & mask16); //put count of each 32 bits into those 32 bits 
	return x;
}
/*
* bitOr - x|y using only ~ and &
*   Example: bitOr(6, 5) = 7
*   Legal ops: ~ &
*   Max ops: 8
*   Rating: 1
*/
int bitOr(int x, int y) {
	/*simply apply deMorgan's law on the following statement would equal to x|y*/
	return ~(~x & ~y);
}
/*
* bitRepeat - repeat x's low-order n bits until word is full.
*   Can assume that 1 <= n <= 32.
*   Examples: bitRepeat(1, 1) = -1
*             bitRepeat(7, 4) = 0x77777777
*             bitRepeat(0x13f, 8) = 0x3f3f3f3f
*             bitRepeat(0xfffe02, 9) = 0x10080402
*             bitRepeat(-559038737, 31) = -559038737
*             bitRepeat(-559038737, 32) = -559038737
*   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
*             (This is more general than the usual integer coding rules.)
*   Max ops: 40
*   Rating: 4
*/
int bitRepeat(int x, int n) {
	/*
	isolate the bits we need to repeat with a mask,
	then keep shifting and duplicating those same bits to the left,
	until we have shifted more than 31 bits.
	*/
	int first;
	int second;
	int third;
	int fourth;
	int fifth;
	int mask;
	int px;
	int preMask = -1 << (n - 1);
	mask = ~(preMask << 1);
	n = !(n / 32) * n;
	px = x & mask;      //the bits we need to repeat
	first = px << n;
	px = px | first;
	n = !(2 * n / 32) * 2 * n;
	second = px << n;
	px = px | second;
	n = !(2 * n / 32) * 2 * n;
	third = px << n;
	px = px | third;
	n = !(2 * n / 32) * 2 * n;
	fourth = px << n;
	px = px | fourth;
	n = !(2 * n / 32) * 2 * n;
	fifth = px << n;
	px = px | fifth;
	return px;
}
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
	/*
	we determine the number of bits that need to be shifted and find the difference between that amount and 32,
	we then shift x to the left by that amount and shift it back to the right by this same amount,
	we then compare the resulting bits with the initial x and see if they are equal,
	this utilizes the sign smearing property of arithmatic right shift
	*/
	int shiftAmount = 32 + (~n + 1);
	int shiftingX = x << shiftAmount;
	int shiftingX2 = shiftingX >> shiftAmount;
	return !(shiftingX2 ^ x);
}
/*
* getByte - Extract byte n from word x
*   Bytes numbered from 0 (LSB) to 3 (MSB)
*   Examples: getByte(0x12345678,1) = 0x56
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 6
*   Rating: 2
*/
int getByte(int x, int n) {
	/*
	shift x to the right by 8 * n, then mask off the least significant 8 bits,
	since 1 byte is 8 bits, this shift statement would guarantee that the target byte is shifted to the least significant byte.
	*/
	int gettingBytes = x >> (n << 3);
	return gettingBytes & 0xff;
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
	we calculate the result of y-x and takes the sign of this result,
	we also figure out the signs of x and y,
	we then determine if the signs of x and y are the same of different,
	if x and y have the same sign, then we simply return the sign of y-x: return 1 if (y-x) is positive/zero, return 0 if (y-x) is negative,
	if x and y have different signs, then we check if x is negative: if x is negative then y must be positive(return 1), if x is positive then y must be negative(return 0).
	*/
	int diff, xSign, ySign, diffSign, equalSigns;
	diff = y + (~x + 1);
	diffSign = !(diff >> 31);  //gives 1 if diff is pos or zero, gives 0 if diff is neg
	xSign = x >> 31;  //gives 0 if pos, gives -1 if neg
	ySign = y >> 31;  //gives 0 if pos, gives -1 if neg
	equalSigns = ~(xSign ^ ySign); //returns 0 if signs are diff, -1 if same
	return (diffSign & equalSigns) | ((xSign & 1) & ~equalSigns);
	//mask diffSign away if signs of x and y are different

}
/*
* isPositive - return 1 if x > 0, return 0 otherwise
*   Example: isPositive(-1) = 0.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 8
*   Rating: 3
*/
int isPositive(int x) {
	/*
	we exploit the property of ! operator to turn non-zero value into 1 and 0 into 0
	*/
	int isZero = !!x;  //only return 1 when x == 0
	int result = !!!(x >> 31);
	return result & isZero;
}
/*
* logicalShift - shift x to the right by n, using a logical shift
*   Can assume that 0 <= n <= 31
*   Examples: logicalShift(0x87654321,4) = 0x08765432
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 20
*   Rating: 3
*/
int logicalShift(int x, int n) {
	/*we shift x to the right by n and use a mask to isolate only the least significant (32-n) bits*/
	int straightShift = x >> n;
	int preShiftMask = ~0 << (31 + (~n + 1));
	int ShiftMask = ~(preShiftMask << 1);
	return  straightShift & ShiftMask;  //needs more testing
}
/*
* tmin - return minimum two's complement integer
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 4
*   Rating: 1
*/
int tmin(void) {
	/*you just wanna make the most significant bit a 1 and the rest of the bits all 0s*/
	return 1 << 31;    //ayy lmao
}
