#include "genHeap.h"
#include <stdlib.h>

struct Heap {
    Vector* vec;
    Comparator comp;
};

/* =========================================================================
   Internal Helper Functions
   ========================================================================= */

/* Sift down a node to maintain the heap property */
static void HeapifyDown(Heap* _heap, size_t _index) {
    size_t size = VectorSize(_heap->vec);
    size_t leftChild, rightChild, maxIndex;
    void *currentVal, *leftVal, *rightVal, *maxVal;

    while (1) {
        leftChild = 2 * _index + 1;
        rightChild = 2 * _index + 2;
        maxIndex = _index;

        VectorGet(_heap->vec, maxIndex, &maxVal);

        if (leftChild < size) {
            VectorGet(_heap->vec, leftChild, &leftVal);
            /* If left is greater than current max */
            if (_heap->comp(maxVal, leftVal) < 0) {
                maxIndex = leftChild;
                maxVal = leftVal;
            }
        }

        if (rightChild < size) {
            VectorGet(_heap->vec, rightChild, &rightVal);
            /* If right is greater than current max */
            if (_heap->comp(maxVal, rightVal) < 0) {
                maxIndex = rightChild;
                maxVal = rightVal;
            }
        }

        /* If the largest is not the parent, swap and continue */
        if (maxIndex != _index) {
            VectorGet(_heap->vec, _index, &currentVal);
            VectorSet(_heap->vec, _index, maxVal);
            VectorSet(_heap->vec, maxIndex, currentVal);
            _index = maxIndex;
        } else {
            break; /* Heap property satisfied */
        }
    }
}

/* Bubble up a node to maintain the heap property */
static void HeapifyUp(Heap* _heap, size_t _index) {
    size_t parentIndex;
    void *currentVal, *parentVal;

    while (_index > 0) {
        parentIndex = (_index - 1) / 2;
        VectorGet(_heap->vec, _index, &currentVal);
        VectorGet(_heap->vec, parentIndex, &parentVal);

        /* If child is greater than parent, swap */
        if (_heap->comp(parentVal, currentVal) < 0) {
            VectorSet(_heap->vec, parentIndex, currentVal);
            VectorSet(_heap->vec, _index, parentVal);
            _index = parentIndex; /* Move up */
        } else {
            break; /* Heap property satisfied */
        }
    }
}

/* =========================================================================
   API Implementation
   ========================================================================= */

Heap* HeapBuild(Vector* _vector, Comparator _pfComp) {
    Heap* heap;
    size_t size, i;

    if (!_vector || !_pfComp) return NULL;

    heap = (Heap*)malloc(sizeof(Heap));
    if (!heap) return NULL;

    heap->vec = _vector;
    heap->comp = _pfComp;

    size = VectorSize(_vector);
    
    /* Efficient O(N) heap construction: 
       Start from the last non-leaf node and HeapifyDown to the root. */
    if (size > 1) {
        for (i = size / 2; i > 0; --i) {
            HeapifyDown(heap, i - 1);
        }
    }

    return heap;
}

Vector* HeapDestroy(Heap** _heap) {
    Vector* vec;

    if (!_heap || !*_heap) return NULL;

    vec = (*_heap)->vec;
    free(*_heap);
    *_heap = NULL;

    return vec;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element) {
    Vector_Result vRes;

    if (!_heap || !_element) return HEAP_NOT_INITIALIZED;

    vRes = VectorAppend(_heap->vec, _element);
    if (vRes == VECTOR_ALLOCATION_ERROR) {
        return HEAP_REALLOCATION_FAILED;
    } else if (vRes != VECTOR_SUCCESS) {
        return HEAP_NOT_INITIALIZED;
    }

    /* Maintain heap property from the newly inserted bottom node */
    HeapifyUp(_heap, VectorSize(_heap->vec) - 1);

    return HEAP_SUCCESS;
}

const void* HeapPeek(const Heap* _heap) {
    void* topElement;

    if (!_heap || VectorSize(_heap->vec) == 0) return NULL;

    if (VectorGet(_heap->vec, 0, &topElement) != VECTOR_SUCCESS) {
        return NULL;
    }

    return topElement;
}

void* HeapExtract(Heap* _heap) {
    void* topElement;
    void* lastElement;
    size_t size;

    if (!_heap) return NULL;
    
    size = VectorSize(_heap->vec);
    if (size == 0) return NULL;

    /* Get the root (top) element */
    VectorGet(_heap->vec, 0, &topElement);

    /* Remove the last element in the array */
    VectorRemove(_heap->vec, &lastElement);

    /* If the heap isn't empty now, put the last element at the root and sift down */
    if (size > 1) {
        VectorSet(_heap->vec, 0, lastElement);
        HeapifyDown(_heap, 0);
    }

    return topElement;
}

size_t HeapSize(const Heap* _heap) {
    if (!_heap) return 0;
    return VectorSize(_heap->vec);
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context) {
    size_t i, size, count = 0;
    void* currentVal;

    if (!_heap || !_act) return 0;

    size = VectorSize(_heap->vec);
    for (i = 0; i < size; ++i) {
        VectorGet(_heap->vec, i, &currentVal);
        count++;
        if (_act(currentVal, _context) == 0) {
            break;
        }
    }

    return count;
}