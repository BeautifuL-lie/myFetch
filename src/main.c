#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "print.h"
#include "utils.h"

int clrscr = 0;
int customconf = 0;

int main(int argc, char *argv[]) {
    int opt;
    opterr = 0;
    char *custom_path_config;

    while ((opt = getopt(argc, argv, ":chf:")) != -1) {
        switch (opt) {
        case 'c':
            clrscr = 1;
            break;
        case 'h':
            printusage(argv[0]);
            return 0;
        case 'f':
            customconf = 1;
            custom_path_config = optarg;
            break;
        case ':':
            printf("\nOption '-%c' needs argument\n", optopt);
            return 1;
        case '?':
            fprintf(stderr, "\n'-%c' is not a valid option\n", optopt);
            printusage(argv[0]);
            return 1;
        }
    }

    putchar('\n');
    char *conf = customconf ? custom_path_config : getconf();

    if (conf == NULL && customconf == 0) {
        printf("No valid config\n");
        return 1;
    }
    printinfo(conf);

    return 0;
}
