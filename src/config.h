#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

char *getconf();
void getusedmodules(FILE *file, char *mod[]);

#endif // !CONFIG_H
