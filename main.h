#ifndef MAI_H_
#define MAI_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* func_1.c file */
int only_spaces(char *token);
char *search_path(const char *str);

#endif
