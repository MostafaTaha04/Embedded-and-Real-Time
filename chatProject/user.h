/* user.h */
#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LEN 32
#define MAX_PASSWORD_LEN 32

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    int  is_active;     /* 1 = logged in, 0 = logged out */
    int  socket_fd;     /* TCP socket to this client      */
} User;

User *user_create(const char *username, const char *password, int socket_fd);
void  user_destroy(User *u);

#endif /* USER_H */