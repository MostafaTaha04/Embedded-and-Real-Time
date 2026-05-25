#ifndef EXERCISE_H
#define EXERCISE_H

#define OK 0
#define ERR 1

/* DESCRIPTION:
* Recive an array and its size and return the most common element in the array
* 
*
* INPUTS:
* array: an array of integers
* size: the size of the array
* 
*
*ERRORS:
* not receiving an array or size less than or equal to 0
*
*
*
*OUTPUTS:
* the most common element in the array
*
*
*/
int most_common(int arr[], int size);


/* DESCRIPTION:
* receive an array and its size and sort the array that the 
* even numbers are in the first part of the array and the 
* odd numbers are in the second part of the array
*
* INPUTS:
* array: an array of integers
* size: the size of the array
*
*
* ERRORS:
* not receiving an array or size less than or equal to 0
* 
*
* OUTPUTS:
* the count of even numbers in the array 
* and the array is sorted in place
*
*/
int even_odd(int arr[], int size);


/* DESCRIPTION:
* receive an array and its size and sort the array in ascending order
*
*
* INPUTS:
* array: an array of integers
* size: the size of the array
*
*
* ERRORS:
* not receiving an array or size less than or equal to 0
*
*
* OUTPUTS:
* the sorted array in ascending order
*
*
*
*/
void ascending_array(int arr[], int size);


/* DESCRIPTION:
* receive an array and its size  
* all the elements in the array are either 0 or 1
* sort the array that all the 0s are in the first part of the array and all the 1s are in the second part of the array
*
* INPUTS:
* array: an array of integers
* size: the size of the array
*
* ERRORS:
* not receiving an array or size less than or equal to 0
* receiving an array that contains elements other than 0 and 1
* 
*
* OUTPUTS:
* sorted array in place that all the 0s are in the first part of the array and all the 1s are in the second part of the array
* 
*
*
*/
void zeros_first_ones_last(int arr[], int size);


#endif 