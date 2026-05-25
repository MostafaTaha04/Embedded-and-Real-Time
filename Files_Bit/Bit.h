#ifndef BIT_H
#define BIT_H

#define OK 0
#define ERR 1

/* DESCRIPTION:
* Helper function to print an unsigned char in binary format.
*
* INPUTS:
* val: the unsigned char to print.
*
* OUTPUTS:
* Prints the binary representation of 'val' to the console.
*/
void printBinaryChar(unsigned char val);

/* DESCRIPTION:
* Inverts the bits of an unsigned char x and stores the answer in y.
* Prints both x and the inverted result in binary form.
*
* INPUTS:
* x: the original unsigned char.
* y: pointer to an unsigned char where the inverted result will be stored.
*
* ERRORS:
* Returns ERR if y is NULL.
*
* OUTPUTS:
* Returns OK if successful.
* Prints the binary forms as specified.
*/
int invertBits(unsigned char x, unsigned char *y);

/* DESCRIPTION:
* Rotates (not shifts) the bits of an unsigned char x to the right by n positions.
* No bits are lost; bits shifted off the right end wrap around to the left.
* Prints the original and rotated values in binary form.
*
* INPUTS:
* x: the unsigned char to rotate.
* n: the number of bit positions to rotate right.
*
* OUTPUTS:
* Returns the rotated unsigned char.
* Prints the binary forms as specified.
*/
unsigned char rotateRight(unsigned char x, int n);

/* DESCRIPTION:
* Returns x with the n bits that begin at position p set to the rightmost n bits 
* of an unsigned char variable y (leaving other bits unchanged).
* Position 0 is the rightmost (least significant) bit.
*
* INPUTS:
* x: the target unsigned char.
* p: the starting position in x (0 to 7).
* n: the number of bits to set.
* y: the source unsigned char containing the bits to copy from its rightmost end.
*
* OUTPUTS:
* Returns the modified unsigned char x.
* Prints the inputs and result in binary form.
*/
unsigned char setbits(unsigned char x, int p, int n, unsigned char y);

/* DESCRIPTION:
* Reverses the order of bits in an unsigned int.
* The most significant bit (MSB) swaps with the least significant bit (LSB), and so on.
*
* INPUTS:
* val: the unsigned int whose bits are to be reversed.
*
* OUTPUTS:
* Returns the unsigned int with reversed bits.
*/
unsigned int reverseBits(unsigned int val);

#endif /* BIT_H */