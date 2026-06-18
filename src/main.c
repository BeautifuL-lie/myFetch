#include "fetch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getconf();
void printinfo(char *conf);
void clearscreen();

int clrscr = 0;

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "c")) != -1) {
        switch (opt) {
            case 'c':
                clrscr = 1;
                break;
            case '?':
                fprintf(stderr, "'-%c' is not a valid option\n", optopt);
                return 1;
        }
    }

    putchar('\n');
    char *conf = getconf();

    if (conf == NULL) {
        printf("NO VALID CONFIG\n");
        return 0;
    }
    printinfo(conf);

    return 0;
}

void clearscreen() {
    // \e[1;1H moves cursor to row 1, column 1
    // \e[2J clears the entire screen
    printf("\e[1;1H\e[2J"); 
}

char *getconf() {
    static char path[256];
    char *xdg_dir = getenv("XDG_CONFIG_HOME");
    char *home_dir = getenv("HOME");
    char *default_dir = "/etc/xdg/myfetch/config";
    char *relative_dir = "config/config";

    if (xdg_dir) {
        snprintf(path, sizeof(path), "%s/myfetch/config", xdg_dir);
        if (access(path, F_OK | R_OK) == 0) {
            return path;
        }
    }

    if (home_dir) {
        snprintf(path, sizeof(path), "%s/.config/myfetch/config", home_dir);
        if (access(path, F_OK | R_OK) == 0) {
            return path;
        }
    }

    if (access(default_dir, F_OK | R_OK) == 0) {
        return default_dir;
    }

    if (access(relative_dir, F_OK | R_OK) == 0) {
        return relative_dir;
    }

    return NULL;
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

    if (clrscr) {
        clearscreen();
        putchar('\n');
    }

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
    fclose(config_file);
}
