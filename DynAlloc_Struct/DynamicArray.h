#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define MAX_SIZE 100


struct DynamicArray {
    int *dArray;
    int dArraySize;
    int dArrayBlockSize;
    int NumOfElements;
};

struct Person{
    int id;
    char name[50];
};

typedef enum {
    OK = 0,
    ERR_NULL_PTR,
    ERR_ALLOCATION_FAILED,
    ERR_INVALID_ARGS,
    ERR_ARRAY_EMPTY
} DynamicArrayError;


/* DESCRIPTION:
* Receives an array of persons and its size, and sorts it according to the ID.
* 
*
* INPUTS:
* arr - an array of Person structs
* size - the number of elements in the array
*
* ERRORS:
* Returns ERR if the array pointer is NULL
*
*
*
* OUTPUTS:
* Returns OK on success, or ERR on failure. The array is sorted in place. 
*
*
*/
int arrayIDSort(struct Person arr[], int size);

/* DESCRIPTION:
* Receives an array of persons and its size, and sorts it according to the name.
*
*
*
* INPUTS:
* arr - an array of Person structs
* size - the number of elements in the array
*
* ERRORS:
* Returns ERR if the array pointer is NULL
*
*
*
* OUTPUTS:
* Returns OK on success, or ERR on failure. The array is sorted in place.
*
*
*/
int arrayNameSort(struct Person arr[], int size);






/* DESCRIPTION:
* 
* 
*
* INPUTS:
* 
* 
*
*ERRORS:
*
*
*
*
*OUTPUTS:
* 
*
*
*/
struct DynamicArray * DynamicArrayCreate( int size, int blockSize);

/* DESCRIPTION:
* 
* 
*
* INPUTS:
* 
* 
*
*ERRORS:
*
*
*
*
*OUTPUTS:
* 
*
*
*/
void DynamicArrayDestroy( struct DynamicArray *DynaminArrayPtr);

/* DESCRIPTION:
* 
* 
*
* INPUTS:
* 
* 
*
* ERRORS:
*
*
*
*
*OUTPUTS:
* 
*
*
*/
DynamicArrayError DynamicArrayInsert(struct DynamicArray *DynaminArrayPtr, int data);

/* DESCRIPTION:
* 
* 
*
* INPUTS:
* 
* 
*
*ERRORS:
*
*
*
*
*OUTPUTS:
* 
*
*
*/
DynamicArrayError DynamicArrayDelete(struct DynamicArray *DynaminArrayPtr, int* data);

#endif 