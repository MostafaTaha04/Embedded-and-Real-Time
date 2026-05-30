/* free_mc_ip_queue.h */
#ifndef FREE_MC_IP_QUEUE_H
#define FREE_MC_IP_QUEUE_H

#include "ds.h"

#define MC_IP_POOL_START "239.1.0.1"
#define MC_IP_POOL_SIZE   200

typedef struct {
    Queue *available;   /* Queue of (char*) free multicast IPs */
} FreeMcIpQueue;

FreeMcIpQueue *mc_queue_create(void);
void           mc_queue_destroy(FreeMcIpQueue *q);
char          *mc_queue_allocate(FreeMcIpQueue *q);          /* returns strdup'd IP */
void           mc_queue_release(FreeMcIpQueue *q, char *ip); /* returns IP to pool  */
int            mc_queue_available(FreeMcIpQueue *q);

#endif /* FREE_MC_IP_QUEUE_H */