/* group_hash.h */
#ifndef GROUP_HASH_H
#define GROUP_HASH_H

#include "ds.h"
#include "group.h"

typedef struct {
    HashTable *table;
} GroupHash;

GroupHash *group_hash_create(void);
void       group_hash_destroy(GroupHash *gh);
int        group_hash_add(GroupHash *gh, Group *g);
Group     *group_hash_get(GroupHash *gh, const char *name);
int        group_hash_remove(GroupHash *gh, const char *name);
int        group_hash_exists(GroupHash *gh, const char *name);
void       group_hash_foreach(GroupHash *gh,
                               void (*cb)(const char *, void *, void *),
                               void *arg);

#endif /* GROUP_HASH_H */