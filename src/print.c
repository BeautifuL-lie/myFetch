#include <stdio.h>
#include <string.h>

#include "config.h"
#include "fetch.h"
#include "struct.h"
#include "utils.h"

void printinfo(char *conf) {
    Info p = {0};
    Info *ptr = &p;
    char *mod[20];

    FILE *config_file = fopen(conf, "r");
    if (!config_file) {
        printf("fail to open config file\n");
        return;
    }

    getusedmodules(config_file, mod);
    get_info(ptr, mod);
    rewind(config_file);
    extern int clrscr;
    if (clrscr) {
        clearscreen();
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
        } else if (strcmp(line, "chasis") == 0) {
            printf("\033[0;33mchasis\033[0m\t%s\n", ptr->chasis);
        }
    }
    fclose(config_file);
}
