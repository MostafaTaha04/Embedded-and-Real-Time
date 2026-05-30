#define _POSIX_C_SOURCE 200809L
#include "server_mng.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    ServerMng *sm = server_mng_create(SERVER_TCP_PORT);
    if (!sm) {
        fprintf(stderr, "Failed to create server\n");
        return 1;
    }
    server_mng_run(sm);
    server_mng_destroy(sm);
    return 0;
}