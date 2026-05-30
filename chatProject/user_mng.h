/* user_mng.h */
#ifndef USER_MNG_H
#define USER_MNG_H

#include "user_hash.h"

typedef struct {
    UserHash *users;
} UserMng;

UserMng *user_mng_create(void);
void     user_mng_destroy(UserMng *um);
int      user_mng_register(UserMng *um, const char *username,
                            const char *password, int socket_fd);
int      user_mng_login(UserMng *um, const char *username,
                         const char *password, int socket_fd);
int      user_mng_logout(UserMng *um, const char *username);
User    *user_mng_get(UserMng *um, const char *username);

#endif /* USER_MNG_H */