#include <stdio.h>
#include <stdlib.h>
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
