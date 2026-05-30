#define _POSIX_C_SOURCE 200809L
#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLR  "\033[2J\033[H"
#define BOLD "\033[1m"
#define RED  "\033[31m"
#define GRN  "\033[32m"
#define CYN  "\033[36m"
#define RST  "\033[0m"

static void _read_line(const char *prompt, char *buf, int len) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, len, stdin))
        buf[strcspn(buf, "\n")] = '\0';
}

static int screen1(ClientMng *cm) {
    char choice[8];
    char user[MAX_USERNAME_LEN];
    char pass[MAX_PASSWORD_LEN];
    int  rc;

    while (1) {
        printf(CLR);
        printf(BOLD CYN
               "==============================\n"
               "      LAN CHAT APPLICATION    \n"
               "==============================\n" RST);
        printf("  1. Register\n");
        printf("  2. Login\n");
        printf("  3. Exit\n");
        printf(CYN "------------------------------\n" RST);

        _read_line("Choice: ", choice, sizeof(choice));

        if (choice[0] == '3') return 0;
        if (choice[0] != '1' && choice[0] != '2') continue;

        _read_line("Username: ", user, sizeof(user));
        _read_line("Password: ", pass, sizeof(pass));

        if (choice[0] == '1')
            rc = client_mng_register(cm, user, pass);
        else
            rc = client_mng_login(cm, user, pass);

        if (rc == 0) {
            printf(GRN "OK  %s\n" RST, client_mng_last_msg(cm));
            if (choice[0] == '2') return 1;
        } else {
            printf(RED "ERR %s\n" RST, client_mng_last_msg(cm));
        }
        printf("Press ENTER to continue...");
        getchar();
    }
}

static void screen2(ClientMng *cm) {
    char choice[8];
    char gname[MAX_GROUP_NAME_LEN];
    int  rc;

    while (1) {
        printf(CLR);
        printf(BOLD CYN
               "==============================\n");
        printf("  Welcome, %s\n", cm->username);
        printf("==============================\n" RST);
        printf("  1. Create group\n");
        printf("  2. Join group\n");
        printf("  3. Leave group\n");
        printf("  4. Logout\n");
        printf(CYN "------------------------------\n" RST);

        _read_line("Choice: ", choice, sizeof(choice));
        rc = 0;

        switch (choice[0]) {
        case '1':
            _read_line("Group name: ", gname, sizeof(gname));
            rc = client_mng_create_group(cm, gname);
            break;
        case '2':
            _read_line("Group name: ", gname, sizeof(gname));
            rc = client_mng_join_group(cm, gname);
            break;
        case '3':
            _read_line("Group name: ", gname, sizeof(gname));
            rc = client_mng_leave_group(cm, gname);
            break;
        case '4':
            client_mng_logout(cm);
            return;
        default:
            continue;
        }

        if (rc == 0)
            printf(GRN "OK  %s\n" RST, client_mng_last_msg(cm));
        else
            printf(RED "ERR %s\n" RST, client_mng_last_msg(cm));

        printf("Press ENTER to continue...");
        getchar();
    }
}

void ui_run(ClientMng *cm) {
    int result;
    while (1) {
        result = screen1(cm);
        if (result == 0) {
            client_mng_exit(cm);
            break;
        }
        screen2(cm);
    }
}