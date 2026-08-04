#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void getusedmodules(FILE *file, char *mod[]) {
    if (!file) {
        printf("can't open config file");
        return;
    }

    char line[50];
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "hostname") == 0) {
            mod[i] = "hostname";
            i++;
        } else if (strcmp(line, "os") == 0) {
            mod[i] = "os";
            i++;
        } else if (strcmp(line, "kernel") == 0) {
            mod[i] = "kernel";
            i++;
        } else if (strcmp(line, "shell") == 0) {
            mod[i] = "shell";
            i++;
        } else if (strcmp(line, "cpu") == 0) {
            mod[i] = "cpu";
            i++;
        } else if (strcmp(line, "memory") == 0) {
            mod[i] = "memory";
            i++;
        } else if (strcmp(line, "uptime") == 0) {
            mod[i] = "uptime";
            i++;
        } else if (strcmp(line, "chasis") == 0) {
            mod[i] = "chasis";
            i++;
        }
    }
    mod[i] = NULL;
}
