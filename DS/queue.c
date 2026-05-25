#include "genqueue.h"
#include <stdlib.h>
#include <assert.h>

#define QUEUE_MAGIC 0x8BADF00D

struct Queue {
    void** m_que;
    size_t m_size;    /* Maximum capacity */
    size_t m_head;    /* Index to read/remove from */
    size_t m_tail;    /* Index to write/insert to */
    size_t m_nItems;  /* Current number of elements */
    unsigned int m_magic;
};

Queue* QueueCreate(size_t _size) {
    Queue* q;

    if (_size == 0) {
        return NULL;
    }

    q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        return NULL;
    }

    q->m_que = (void**)malloc(_size * sizeof(void*));
    if (q->m_que == NULL) {
        free(q);
        return NULL;
    }

    q->m_size = _size;
    q->m_head = 0;
    q->m_tail = 0;
    q->m_nItems = 0;
    q->m_magic = QUEUE_MAGIC;

    return q;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy) {
    size_t i, index;

    if (_queue == NULL || *_queue == NULL || (*_queue)->m_magic != QUEUE_MAGIC) {
        return;
    }

    if (_itemDestroy != NULL) {
        /* Iterate over active items using modulo arithmetic */
        for (i = 0; i < (*_queue)->m_nItems; ++i) {
            index = ((*_queue)->m_head + i) % (*_queue)->m_size;
            _itemDestroy((*_queue)->m_que[index]);
        }
    }

    free((*_queue)->m_que);
    (*_queue)->m_magic = 0; /* Invalidate */
    free(*_queue);
    *_queue = NULL;
}

QueueResult QueueInsert(Queue* _queue, void* _item) {
    if (_queue == NULL || _queue->m_magic != QUEUE_MAGIC) {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    if (_item == NULL) {
        return QUEUE_DATA_UNINITIALIZED_ERROR;
    }

    if (_queue->m_nItems == _queue->m_size) {
        return QUEUE_OVERFLOW_ERROR;
    }

    _queue->m_que[_queue->m_tail] = _item;
    
    /* Circular wrap around for the tail */
    _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
    _queue->m_nItems++;

    return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue* _queue, void** _item) {
    if (_queue == NULL || _queue->m_magic != QUEUE_MAGIC) {
        return QUEUE_UNINITIALIZED_ERROR;
    }

    assert(_item != NULL);

    if (_queue->m_nItems == 0) {
        return QUEUE_DATA_NOT_FOUND_ERROR;
    }

    *_item = _queue->m_que[_queue->m_head];
    
    /* Circular wrap around for the head */
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    _queue->m_nItems--;

    return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue) {
    if (_queue == NULL || _queue->m_magic != QUEUE_MAGIC) {
        return 1; /* Treat invalid queues as empty */
    }
    return _queue->m_nItems == 0 ? 1 : 0;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context) {
    size_t i, index;
    size_t invocations = 0;

    if (_queue == NULL || _queue->m_magic != QUEUE_MAGIC || _action == NULL) {
        return 0;
    }

    for (i = 0; i < _queue->m_nItems; ++i) {
        index = (_queue->m_head + i) % _queue->m_size;
        invocations++;
        
        if (_action(_queue->m_que[index], _context) == 0) {
            break;
        }
    }

    return invocations;
}