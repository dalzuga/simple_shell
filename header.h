#ifndef HEADER_H
#define HEADER_H

#ifndef BUF_SIZE
#define BUF_SIZE 256
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> /* ~wait(2)~ */
#include <string.h>   /* ~strtok(3)~ */
#include <sys/stat.h> /* stat(2) */

/* this function prints the simple shell user prompt */
int *print_prompt();
/* this function prints a character */
int print_char(char c);

void print_buffer(void *ptr, size_t nmemb);
void print_horizontal_bar(unsigned long int n);
void strip_newline(char *s, ssize_t read);
char *get_fpath(char *cmd, char **env);
void _memset(void *s, int c, size_t n);
int _strncmp(char *s1, char *s2, int n);
void print_grid(char **grid);
void print_string(char *s);
char handle_builtins(char *cmd, char *line, char **env);
void _free(char *line);
char handle_exec(char *cmd, char *line, char **env);
int _strlen(const char *str);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
void canary(const char *s);
int atoi(const char *s);


#endif
