#define _POSIX_C_SOURCE 200809L
#include "ui.h"
#include "client_mng.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    ClientMng  *cm;
    const char *server_ip = (argc >= 2) ? argv[1] : "127.0.0.1";
    cm = client_mng_create(server_ip);
    if (!cm) {
        fprintf(stderr, "Failed to connect to server at %s\n", server_ip);
        return 1;
    }
    ui_run(cm);
    client_mng_destroy(cm);
    return 0;
}