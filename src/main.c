#include "fetch.h"
#include <stdio.h>

int main() {
    char user[50];
    char os[50];
    char kernel[50];
    char hostname[50];
    char shell[50];
    char cpu[50];
    char memory[50];
    char uptime[50];
    
    putchar('\n');

    get_user(user, sizeof(user));
    get_hostname(hostname, sizeof(hostname));
    printf("\033[0;34m%s@%s\033[0m\n", user, hostname);

    get_os(os, sizeof(os));
    printf("\033[0;33mos\033[0m\t%s\n", os);

    get_kernel(kernel, sizeof(kernel));
    printf("\033[0;33mkernel\033[0m\t%s\n", kernel);

    get_shell(shell, sizeof(shell));
    printf("\033[0;33mshell\033[0m\t%s\n", shell);
    
    get_cpu(cpu, sizeof(cpu));
    printf("\033[0;33mcpu\033[0m\t%s\n", cpu);

    get_memory(memory, sizeof(memory));
    printf("\033[0;33mmemory\033[0m\t%s\n", memory);

    get_uptime(uptime, sizeof(uptime));
    printf("\033[0;33muptime\033[0m\t%s\n", uptime);
    
    return 0;
}
