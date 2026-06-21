#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "print.h"
#include "utils.h"

int clrscr = 0;

int main(int argc, char *argv[]) {
    int opt;
    opterr = 0;

    while ((opt = getopt(argc, argv, "ch")) != -1) {
        switch (opt) {
            case 'c':
                clrscr = 1;
                break;
            case 'h':
                printusage(argv[0]);
                return 0;
            case '?':
                fprintf(stderr, "\n'-%c' is not a valid option\n", optopt);
                printusage(argv[0]);
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
