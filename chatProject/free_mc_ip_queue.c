#define _POSIX_C_SOURCE 200809L
#include "free_mc_ip_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FreeMcIpQueue *mc_queue_create(void) {
    int   i;
    char *ip;
    FreeMcIpQueue *q = malloc(sizeof(FreeMcIpQueue));
    if (!q) return NULL;
    q->available = queue_create();

    for (i = 1; i <= MC_IP_POOL_SIZE; i++) {
        ip = malloc(16);
        if (!ip) continue;
        snprintf(ip, 16, "239.1.0.%d", i);
        queue_enqueue(q->available, ip);
    }
    return q;
}

void mc_queue_destroy(FreeMcIpQueue *q) {
    if (!q) return;
    queue_destroy(q->available, free);
    free(q);
}

char *mc_queue_allocate(FreeMcIpQueue *q) {
    if (!q || queue_is_empty(q->available)) return NULL;
    return (char *)queue_dequeue(q->available);
}

void mc_queue_release(FreeMcIpQueue *q, char *ip) {
    if (!q || !ip) return;
    queue_enqueue(q->available, ip);
}

int mc_queue_available(FreeMcIpQueue *q) {
    return q ? queue_size(q->available) : 0;
}