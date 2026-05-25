#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>

typedef struct Queue Queue;

typedef enum Queue_Result {
    QUEUE_SUCCESS = 0,
    QUEUE_UNINITIALIZED_ERROR,
    QUEUE_ALLOCATION_ERROR,
    QUEUE_UNDERFLOW_ERROR
} Queue_Result;

Queue* QueueCreate(void);
void QueueDestroy(Queue** _queue, void (*_elementDestroy)(void* _item));
Queue_Result QueueEnqueue(Queue* _queue, void* _item);
Queue_Result QueueDequeue(Queue* _queue, void** _pItem);
size_t QueueSize(const Queue* _queue);

#endif /* __QUEUE_H__ */