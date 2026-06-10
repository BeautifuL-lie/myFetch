#include "fetch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getconf();
void printinfo(char *conf);

int main() {
    putchar('\n');
    char *conf = getconf();

    if (conf == NULL) {
        printf("NO VALID CONFIG\n");
        return 0;
    }
    printinfo(conf);

    return 0;
}

char *getconf() {
    static char path[256];
    char *xdg_dir = getenv("XDG_CONFIG_HOME");
    char *home_dir = getenv("HOME");

    if (xdg_dir) {
        snprintf(path, sizeof(path), "%s/myfetch/myfetch/config", xdg_dir);
    } else if (!xdg_dir && home_dir) {
        snprintf(path, sizeof(path), "%s/.config/myfetch/config", home_dir);
    } else {
        // printf("CONFIG DIR NOT FOUND\n");
        return NULL;
    }

    FILE *conf = fopen(path, "r");

    if (!conf) {
        // printf("CONFIG FILE NOT FOUND\n");
        return NULL;
    }

    return path;
}

void printinfo(char *conf) {
    Info p = {0};
    Info *ptr = &p;

    FILE *config_file = fopen(conf, "r");
    if (!config_file) {
        printf("fail to open config file\n");
        return;
    }

    get_info(ptr);

    char line[256];
    while (fgets(line, sizeof(line), config_file) != NULL) {
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "hostname") == 0) {
            printf("\033[0;34m%s@%s\033[0m\n", ptr->user, ptr->hostname);
        } else if (strcmp(line, "os") == 0) {
            printf("\033[0;33mos\033[0m\t%s\n", ptr->os);
        } else if (strcmp(line, "kernel") == 0) {
            printf("\033[0;33mkernel\033[0m\t%s\n", ptr->kernel);
        } else if (strcmp(line, "shell") == 0) {
            printf("\033[0;33mshell\033[0m\t%s\n", ptr->shell);
        } else if (strcmp(line, "cpu") == 0) {
            printf("\033[0;33mcpu\033[0m\t%s\n", ptr->cpu);
        } else if (strcmp(line, "memory") == 0) {
            printf("\033[0;33mmemory\033[0m\t%s\n", ptr->memory);
        } else if (strcmp(line, "uptime") == 0) {
            printf("\033[0;33muptime\033[0m\t%s\n", ptr->uptime);
        }
    }
}
