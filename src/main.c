#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "print.h"

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
