#ifndef FILES_H
#define FILES_H

#define OK 0
#define ERR 1   
#define MAX_LINE_LENGTH 1000
#define MAX_LINES 1000


/* DESCRIPTION: 
*  Swaps the values of two integers.
*
*
* input:
* a: a pointer to the first integer
* b: a pointer to the second integer
*
* output:
* None
*/
static void swap_func(int *a, int *b);


/* DESCRIPTION:
* receive a filename and a number n and print the last n lines of the file
* 
*
* INPUTS:
* filename: the name of the file to read
* n: the number of lines to print from the end of the file
* 
*
* ERRORS:
* not receiving a filename or n less than or equal to 0
*
*
*
* OUTPUTS:
* OK if successful, ERR if an error occurs
* and the last n lines of the file are printed to the console
*
*/
int printLastNLines(const char* filename, int n);


/* DESCRIPTION:
* Counts and prints the number of lines, words, and characters in a file.
* 
*
* INPUTS:
* filename: the name of the file to analyze.
*
* 
*
* ERRORS:
* not receiving a filename or the file cannot be opened.
* 
*
*
*
* OUTPUTS:
* OK if successful, ERR if an error occurs
* and the number of lines, words, and characters in the file are printed to the console
*/
int printRowsColumnsCharsNumbers(const char* filename);


#endif 