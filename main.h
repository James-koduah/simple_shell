#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \n"
/* read user input from command line */
void _getline(char **line);
/* execute PATH */
char *search_path(const char *command);
/* print environment variables */
void print_env(void);
extern char **environ;

#endif /* _MAIN_H */
