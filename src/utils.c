#include <stdio.h>

void clearscreen() {
    printf("\e[1;1H\e[2J"); 
}

void printusage(char *app) {
    printf("Usage: %s [OPTION]\n\n", app);
    printf("  -c, \tclear the screen before shows the output\n");
    printf("  -h, \tshow this help message\n");
}
