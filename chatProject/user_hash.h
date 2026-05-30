/* user_hash.h */
#ifndef USER_HASH_H
#define USER_HASH_H

#include "ds.h"
#include "user.h"

typedef struct {
    HashTable *table;
} UserHash;

UserHash *user_hash_create(void);
void      user_hash_destroy(UserHash *uh);
int       user_hash_add(UserHash *uh, User *u);
User     *user_hash_get(UserHash *uh, const char *username);
int       user_hash_remove(UserHash *uh, const char *username);
int       user_hash_exists(UserHash *uh, const char *username);

#endif /* USER_HASH_H */