#include "genvec.h"
#include <stdlib.h>

struct Vector {
    void** items;
    size_t capacity;
    size_t size;
    size_t blockSize;
};

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize) {
    Vector* vec;

    if (_initialCapacity == 0 && _blockSize == 0) {
        return NULL;
    }

    vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) return NULL;

    vec->items = (void**)malloc(_initialCapacity * sizeof(void*));
    if (!vec->items && _initialCapacity > 0) {
        free(vec);
        return NULL;
    }

    vec->capacity = _initialCapacity;
    vec->size = 0;
    vec->blockSize = _blockSize;

    return vec;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item)) {
    Vector* vec;
    size_t i;

    if (!_vector || !*_vector) return;
    
    vec = *_vector;

    if (_elementDestroy) {
        for (i = 0; i < vec->size; ++i) {
            _elementDestroy(vec->items[i]);
        }
    }

    free(vec->items);
    free(vec);
    *_vector = NULL;
}

Vector_Result VectorAppend(Vector* _vector, void* _item) {
    void** newItems;
    size_t newCapacity;

    if (!_vector || !_item) return VECTOR_UNINITIALIZED_ERROR;

    if (_vector->size == _vector->capacity) {
        if (_vector->blockSize == 0) return VECTOR_ALLOCATION_ERROR;
        
        newCapacity = _vector->capacity + _vector->blockSize;
        newItems = (void**)realloc(_vector->items, newCapacity * sizeof(void*));
        if (!newItems) return VECTOR_ALLOCATION_ERROR;

        _vector->items = newItems;
        _vector->capacity = newCapacity;
    }

    _vector->items[_vector->size++] = _item;
    return VECTOR_SUCCESS;
}

Vector_Result VectorRemove(Vector* _vector, void** _pValue) {
    if (!_vector || !_pValue) return VECTOR_UNINITIALIZED_ERROR;
    if (_vector->size == 0) return VECTOR_UNDERFLOW_ERROR;

    *_pValue = _vector->items[--_vector->size];
    return VECTOR_SUCCESS;
}

Vector_Result VectorGet(const Vector* _vector, size_t _index, void** _pValue) {
    if (!_vector || !_pValue) return VECTOR_UNINITIALIZED_ERROR;
    if (_index >= _vector->size) return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;

    *_pValue = _vector->items[_index];
    return VECTOR_SUCCESS;
}

Vector_Result VectorSet(Vector* _vector, size_t _index, void* _value) {
    if (!_vector || !_value) return VECTOR_UNINITIALIZED_ERROR;
    if (_index >= _vector->size) return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;

    _vector->items[_index] = _value;
    return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector) {
    if (!_vector) return 0;
    return _vector->size;
}