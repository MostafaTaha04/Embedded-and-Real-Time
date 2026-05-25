#ifndef ASS_H
#define ASS_H

#define Array_size 60000

/* Description: 
* Reverses the bits of an unsigned integer using a lookup table.
*
* input:
* n - the unsigned integer whose bits are to be reversed
*
* output:
* the unsigned integer with reversed bits
*/
unsigned int reverseBitLUT(unsigned int n);

/* Description: 
* Swaps the values of two integers using pointers.
*
* input:
* a - a pointer to the first integer
* b - a pointer to the second integer
*
* output:
* None (void)
*/
void swap_func(int *a, int *b);

/* Description: 
* Sorts an array of integers using the Bubble Sort algorithm 
* by calling a regular swap function.
*
* input:
* arr - the array of integers to be sorted
* n   - the number of elements in the array
*
* output:
* Returns 0 upon completion
*/
int swap_with_func(int arr[], int n);

/* Description: 
* Sorts an array of integers using the Bubble Sort algorithm 
* by utilizing a SWAP macro instead of a function call.
*
* input:
* arr - the array of integers to be sorted
* n   - the number of elements in the array
*
* output:
* None (void)
*/
void sort_with_macro(int arr[], int n);


typedef struct {
    unsigned int right : 4;
    unsigned int left  : 4;
} CharPair;

/* Description: 
* Compresses a string of characters (a-o) into an array of bytes.
* Each byte will contain two 4-bit characters using bitwise operations.
*
* input:
* str        - the original string to be compressed
* compressed - an array of unsigned chars to store the compressed result
*
* output:
* None (void). The result is saved in the 'compressed' array.
*/
void compress_bitwise(const char *str, unsigned char *compressed);

/* Description: 
* Compresses a string of characters (a-o) into an array of CharPair.
* Each CharPair struct will hold two 4-bit characters using bit-fields.
*
* input:
* str        - the original string to be compressed
* compressed - an array of CharPair structs to store the compressed result
*
* output:
* None (void). The result is saved in the 'compressed' array.
*/
void compress_bitfield(const char *str, CharPair *compressed);



/* Description: 
* Sorts an array using a generic Bubble Sort algorithm. 
* The sorting logic is determined by a provided criteria function pointer.
*
* input:
* arr  - the integer array to be sorted
* size - the number of elements in the array
* CR   - a pointer to a criteria function that takes two integers 
* and returns 1 (true) if they need to be swapped, or 0 (false) otherwise.
*
* output:
* None (void). The array is sorted in place.
*/
void generic_bubble_sort(int *arr, int size, int (*CR)(int, int));

#endif 