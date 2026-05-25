#include <stdlib.h>
#include <assert.h>
#include "vector.h"

struct Vector {
    void** m_items;
    size_t m_originalCapacity;
    size_t m_capacity;
    size_t m_size;
    size_t m_blockSize;
};

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize) {
    Vector* vec;

    if (_initialCapacity == 0 && _blockSize == 0) {
        return NULL;
    }

    vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        return NULL;
    }

    vec->m_items = NULL;
    if (_initialCapacity > 0) {
        vec->m_items = (void**)malloc(_initialCapacity * sizeof(void*));
        if (vec->m_items == NULL) {
            free(vec);
            return NULL;
        }
    }

    vec->m_originalCapacity = _initialCapacity;
    vec->m_capacity = _initialCapacity;
    vec->m_size = 0;
    vec->m_blockSize = _blockSize;

    return vec;
}

void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item)) {
    size_t i;
    
    if (_vector == NULL || *_vector == NULL) {
        return;
    }

    if (_elementDestroy != NULL) {
        for (i = 0; i < (*_vector)->m_size; ++i) {
            _elementDestroy((*_vector)->m_items[i]);
        }
    }

    free((*_vector)->m_items);
    free(*_vector);
    *_vector = NULL; 
}

VectorResult VectorAppend(Vector* _vector, void* _item) {
    void** newItems;

    if (_vector == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_vector->m_size == _vector->m_capacity) {
        if (_vector->m_blockSize == 0) {
            return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
        }

        newItems = (void**)realloc(_vector->m_items, (_vector->m_capacity + _vector->m_blockSize) * sizeof(void*));
        if (newItems == NULL) {
            return VECTOR_ALLOCATION_ERROR;
        }

        _vector->m_items = newItems;
        _vector->m_capacity += _vector->m_blockSize;
    }

    _vector->m_items[_vector->m_size] = _item;
    _vector->m_size++;

    return VECTOR_SUCCESS;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue) {
    void** newItems;

    if (_vector == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }
    
    assert(_pValue != NULL);

    if (_vector->m_size == 0) {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    _vector->m_size--;
    *_pValue = _vector->m_items[_vector->m_size];

    if (_vector->m_blockSize > 0 && 
        (_vector->m_capacity - _vector->m_size) >= (_vector->m_blockSize * 2) &&
        (_vector->m_capacity - _vector->m_blockSize) >= _vector->m_originalCapacity) {
        
        newItems = (void**)realloc(_vector->m_items, (_vector->m_capacity - _vector->m_blockSize) * sizeof(void*));
        if (newItems != NULL) {
            _vector->m_items = newItems;
            _vector->m_capacity -= _vector->m_blockSize;
        }
    }

    return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue) {
    if (_vector == NULL || _pValue == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_index >= _vector->m_size) {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    *_pValue = _vector->m_items[_index];
    return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void* _value) {
    if (_vector == NULL) {
        return VECTOR_UNITIALIZED_ERROR;
    }

    if (_index >= _vector->m_size) {
        return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
    }

    _vector->m_items[_index] = _value;
    return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector) {
    if (_vector == NULL) {
        return 0;
    }
    return _vector->m_size;
}

size_t VectorCapacity(const Vector* _vector) {
    if (_vector == NULL) {
        return 0;
    }
    return _vector->m_capacity;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context) {
    size_t i;
    
    if (_vector == NULL || _action == NULL) {
        return 0;
    }

    for (i = 0; i < _vector->m_size; ++i) {
        if (_action(_vector->m_items[i], i, _context) == 0) {
            break;
        }
    }
    
    return i;
}