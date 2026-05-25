#ifndef __GENVEC_H__
#define __GENVEC_H__

#include <stddef.h>

typedef struct Vector Vector;

typedef enum Vector_Result {
    VECTOR_SUCCESS = 0,
    VECTOR_UNINITIALIZED_ERROR,
    VECTOR_ALLOCATION_ERROR,
    VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,
    VECTOR_UNDERFLOW_ERROR
} Vector_Result;

/* Create a new vector */
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize);

/* Destroy the vector */
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item));

/* Append an item to the end of the vector */
Vector_Result VectorAppend(Vector* _vector, void* _item);

/* Remove the last item from the vector */
Vector_Result VectorRemove(Vector* _vector, void** _pValue);

/* Get an item at a specific index */
Vector_Result VectorGet(const Vector* _vector, size_t _index, void** _pValue);

/* Overwrite an item at a specific index (used for swapping in the heap) */
Vector_Result VectorSet(Vector* _vector, size_t _index, void* _value);

/* Get the current number of elements */
size_t VectorSize(const Vector* _vector);

#endif /* __GENVEC_H__ */