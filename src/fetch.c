#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "fetch.h"

void get_os() {
  FILE *file = fopen("/etc/os-release", "r");
    
    if (!file) {
        printf("OS: Unknown\n");
        return;
    }
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
        char *value = strchr(line, '=');
        if (!value) break;
        value++;
        value[strcspn(value, "\n")] = '\0';
        if (*value == '"') value++;
        size_t len = strlen(value);
        if (len > 0 && value[len - 1] == '"')
            value[len - 1] = '\0';
        printf("OS: %s\n", value);
        break;
        }
    }
    fclose(file);
}

void get_kernel() {
    struct utsname u;
    uname(&u);
    printf("Kernel: %s %s\n", u.sysname, u.release);
}

void get_hostname() {
    FILE *file = fopen("/etc/hostname", "r");

    if (!file) {
        printf("Hostname: Unknown\n");
        return;
    }

    char line[50];
  
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = '\0';
    printf("Hostname: %s\n", line);
    fclose(file);
}

void get_shell() {
    char *str = getenv("SHELL");

    if (!str) {
        return;
    }

    char* ptr = strrchr(str, '/');
    if (!ptr) {
        printf("Shell: %s\n", str);
        return;
    }
    
    printf("Shell: %s\n", ptr + 1);
}

void get_cpu() {
    FILE *file = fopen("/proc/cpuinfo", "r");

    if (!file) {
        printf("CPU: Unknown\n");
        return;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)) {
        if (strncmp(line, "model name", 10) == 0) {
            char *value = strchr(line, ':');
            value[strcspn(value, "\n")] = '\0';
            printf("CPU: %s\n", value + 2);
            break;
        }
    }
    fclose(file);
}

void get_memory() {
    FILE *file = fopen("/proc/meminfo", "r");

    if (!file) {
        printf("Memory: N/A\n");
        return;
    }

    char line[256];
    long mem_total = 0, mem_available = 0;
    int found = 0;
    while(fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %ld kB", &mem_total);
            found++;
        } else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %ld kB", &mem_available);
            found++;
        }
        if (found == 2) break;
    }

    fclose(file);
    
     if (mem_total == 0) {
        printf("Memory: N/A\n");
        return;
    }

    double total_gb = mem_total / 1024.0 / 1024.0;
    double avail_gb = mem_available / 1024.0 / 1024.0;
    double used_gb = total_gb - avail_gb;
    int percentage = used_gb / total_gb * 100;

    printf("Memory: %.2f GB / %.2f GB (%d%%)\n", used_gb, total_gb, percentage);
}
