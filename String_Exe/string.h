#ifndef STRING_H
#define STRING_H

#define MAX_STRING_LENGTH 100
#define OK 0
#define ERROR -1

/* Description:
 * Reverses a string in-place.
 *
 * Inputs:
 * _str: the string to be reversed
 * 
 * 
 * Errors:
 * - If _str is NULL, the function returns ERROR (-1).
 * 
 *
 * Return:
 * Returns OK (0) on success, or ERROR (-1) if the input is NULL.
 *  
 */
int ReverseStr(char *_str);

/* Description:
 * Checks if a string is a palindrome.
 *
 * Inputs:
 * _str: the string to be checked (read-only)
 *
 * Errors:
 * - If _str is NULL, the function returns ERROR (-1).
 *
 * Return:
 * Returns OK (0) if the string is a palindrome, otherwise returns ERROR (-1).
 */
int IsPalindrome(char *_str);

/* Description:
 * Converts a string representation of a number to an integer.
 *
 * Inputs:
 * _str: the string to be converted (read-only)
 * _num: pointer to store the resulting integer
 *
 * Errors:
 * - If _str is NULL or _num is NULL, the function returns ERROR (-1).
 * - If _str contains non-numeric characters
 * 
 * Return:
 * Returns OK (0) on success, otherwise returns ERROR (-1).
 */
int MyAToI(char *_str, int *_num);

/* Description:
 * Converts an integer to its string (ASCII) representation.
 *
 * Inputs:
 * _num: the integer to convert
 * _buffer: the character array to store the resulting string
 *
 * Errors:
 * - If _buffer is NULL, the function returns ERROR (-1).
 * - If the resulting string exceeds MAX_STRING_LENGTH, the function returns ERROR (-1).
 * 
 * Return:
 * Returns OK (0) on success, otherwise returns ERROR (-1).
 */
int MyIToA(int _num, char *_buffer);

/* Description:
 * Reverses the order of the words in a string in-place.
 *
 * Inputs:
 * _str: the string to be modified
 *
 * Errors:
 * - If _str is NULL, the function returns ERROR (-1).
 * - If the string contains more than MAX_STRING_LENGTH characters, the function returns ERROR (-1).
 *
 * Return:
 * Returns OK (0) on success, otherwise returns ERROR (-1).
 */
int ReverseWordsInString(char *_str);

/* Description:
 * Counts the number of words in a string.
 *
 * Inputs:
 * _str: the string to be analyzed (read-only)
 *
 * 
 * Errors:
 * - If _str is NULL, the function returns ERROR (-1).
 * - If the string contains more than MAX_STRING_LENGTH characters, the function returns ERROR (-1).
 * 
 * Return:
 * Returns the number of words, or ERROR (-1) if the input is invalid.
 * (Note: If returning word count, consider returning -1 for errors to distinguish from 0 words).
 */
int CountWordsInString(char *_str);

#endif