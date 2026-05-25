#include "queue.h"
#include "dll.h"
#include <stdlib.h>

struct Queue {
    List* dlist;
};

Queue* QueueCreate(void) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) return NULL;

    q->dlist = ListCreate();
    if (!q->dlist) {
        free(q);
        return NULL;
    }
    return q;
}

void QueueDestroy(Queue** _queue, void (*_elementDestroy)(void* _item)) {
    if (!_queue || !*_queue) return;
    ListDestroy(&((*_queue)->dlist), _elementDestroy);
    free(*_queue);
    *_queue = NULL;
}

Queue_Result QueueEnqueue(Queue* _queue, void* _item) {
    if (!_queue || !_item) return QUEUE_UNINITIALIZED_ERROR;
    /* Enqueue means adding to the back (tail) */
    if (ListPushTail(_queue->dlist, _item) == LIST_ALLOCATION_ERROR) {
        return QUEUE_ALLOCATION_ERROR;
    }
    return QUEUE_SUCCESS;
}

Queue_Result QueueDequeue(Queue* _queue, void** _pItem) {
    if (!_queue || !_pItem) return QUEUE_UNINITIALIZED_ERROR;
    /* Dequeue means removing from the front (head) */
    if (ListPopHead(_queue->dlist, _pItem) == LIST_UNDERFLOW_ERROR) {
        return QUEUE_UNDERFLOW_ERROR;
    }
    return QUEUE_SUCCESS;
}

size_t QueueSize(const Queue* _queue) {
    if (!_queue) return 0;
    return ListSize(_queue->dlist);
}