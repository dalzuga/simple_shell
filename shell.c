#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> /* ~wait(2)~ */
#include <string.h>   /* ~strtok(3)~ */
#include <sys/stat.h> /* stat(2) */

#include "header.h"

#ifndef BUF_SIZE
#define BUF_SIZE 256
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

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
int _strlen(char *str);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
void canary();

int main(int __attribute__ ((unused)) argc, char *argv[], char **env)
{
	FILE *fp = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *cmd = NULL;

	fp = stdin;

	while (1)
	{
		print_prompt();

		read = getline(&line, &len, fp);
		/* printf("Len: %lu\n", len); */
		/* printf("Address: %p\n", (void *) line); */

		if (fp == NULL)
		{
			/* if fp is a file which failed to open */
			perror(argv[0]);
			return (EXIT_FAILURE);
		}

		/* handle EOF */
		if (read == EOF)
		{
			_free(line);

			if (errno == 0)
			{
				return (EXIT_SUCCESS);
			}

			/* printf("errno is not 0.\n"); */
			perror(argv[0]);
			return (EXIT_FAILURE);
		}

		/* printf("Read: %d\n", (int) read); */
		/* print_buffer(line, read); */

		cmd = strtok(line, " \n");
		/* handles newline (empty command) + checks for built in */
		if (cmd != NULL && handle_builtins(cmd, line, env))
		{
			/**
			 * PROGRAM EXEC
			 * fork() begins here
			 */

			if (handle_exec(cmd, line, env))
			{
				canary();
				perror(argv[0]);
				return (EXIT_FAILURE);
			}
		}
	}

	return (EXIT_SUCCESS);
}

/* returns 0 if user command is a built-in, 1 otherwise */
char handle_builtins(char *cmd, char *line __attribute__ ((unused)), char **env)
{
	/**
	 * BUILT-INS
	 */

	/* printf("%lu\n", read); */

	if (_strncmp(cmd, "exit", 5) == 0)
	{
		_free(line);
		exit(EXIT_SUCCESS);
	}

	if (_strncmp(cmd, "env", 4) == 0)
	{
		print_grid(env);
		return (0);
	}

	return (1);
}

/* returns 0 on success, returns 1 if something went wrong */
char handle_exec(char *cmd, char *line, char **env)
{
	char *null_ptr[] __attribute__ ((unused)) = { NULL };
	char *cargv[BUF_SIZE]; 		/* child argv */
	int i;
	char *full_exec_path = NULL;
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		return (1);
	}

	if (pid != 0)
	{
		/* we're in the parent process */
		/* printf("Parent start.\n"); */

		/**
		 * wait() waits for a child to terminate. Upon child
		 * termination, wait() stores status information about
		 * the child on the int to which it points.
		 */
		wait(&status);

		/**
		 * ~WIFEXITED~ is a macro to inspect ~status~. It
		 * returns true if the child exited normally.
		 */
		if (WIFEXITED(status))
		{
			/* printf("Child terminated successfully.\n"); */
		}
	} else {
		/* we're in the child process */

		cargv[0] = cmd;

		for (i = 0; i < BUF_SIZE - 1; i++)
		{
			if (cargv[i] == NULL)
			{
				break;
			}

			cargv[i + 1] = strtok(NULL, " \n");
		}

		/* Get absolute path */
		if ((full_exec_path = get_fpath(cmd, env)) == NULL)
		{
			_free(line);
			return (1);
		}

		/* Execute a program */
		if (execve(full_exec_path, cargv, env) == -1)
		{
			_free(line);
			return (1);
		}
	}

	/* execve(line, null_ptr, null_ptr); */
	return (0);
}

void _free(char *line)
{
	free(line);
	line = NULL;
}

/* get_fpath - On memory error, returns NULL */
/* allocates a string in memory which must be freed by the calling function */
char *get_fpath(char *cmd, char **env)
{
	int i, j;
	char PATH_envval[BUF_SIZE];
	char *token;
	char *full_cmd_path;
	long unsigned int full_cmd_len;
	struct stat st;

	if (cmd[0] == '/')
	{
		return (cmd);
	}

	/* find PATH env var */
	for (i = 0; ; i++)
	{
		if (_strncmp(env[i], "PATH=", 5) == 0)
		{
			break;
		}
	}

	/* copy the value of ~$PATH~ onto ~PATH_envval~ */
	for (j = 5; j < BUF_SIZE + 5; j++)
	{
		PATH_envval[j-5] = env[i][j];
	}

	/* let's check each directory */
	token = strtok(PATH_envval, ":");
	while (token != NULL)
	{
		/* check for path: token + "/" + cmd + '\0' */

		full_cmd_len = _strlen(token) + _strlen(cmd) + 2;
		full_cmd_path = malloc(sizeof(char) * full_cmd_len);

		/* memory check */
		if (full_cmd_path == NULL)
		{
			perror("malloc");
			return NULL;
		}

		_memset(full_cmd_path, 0, full_cmd_len);

		/* concat strings */
		full_cmd_path = _strcat(full_cmd_path, token);
		full_cmd_path = _strcat(full_cmd_path, "/");
		full_cmd_path = _strcat(full_cmd_path, cmd);

		/* printf("full_cmd_path: %s\n", full_cmd_path); */

		if (stat(full_cmd_path, &st) == 0)
		{
			/* printf("token: %s\n", token); */
			return (full_cmd_path);
		}

		free(full_cmd_path);

		token = strtok(NULL, ":");
	}

	return (cmd);
}

void strip_newline(char *s, ssize_t read)
{
	if (s[read-1] == '\n')
		s[read-1] = '\0';
}

void print_buffer(void *ptr, size_t nmemb)
{
	unsigned long int i;
	char *tmp_ptr;

	tmp_ptr = ptr;

	print_horizontal_bar(nmemb);
	write(1, "\n", 1);

	write(1, "|", 1);
	for (i = 0; i < nmemb; i++)
	{
		write(1, " ", 1);
		if (*tmp_ptr == 10)
		{
			write(1, "\\n", 2);
		} else {
			write(1, tmp_ptr, 1);
		}
		write(1, " |", 3);
		tmp_ptr++;
	}

	write(1, "\n", 1);
	print_horizontal_bar(nmemb);

	tmp_ptr = ptr;

	write(1, "\n", 1);
	write(1, "|", 1);
	for (i = 0; i < nmemb; i++)
	{
		if (*tmp_ptr == 10)
		{
			printf("%3d |", *tmp_ptr);
			fflush(stdout);
		} else {
			printf("%3d|", *tmp_ptr);
			fflush(stdout);
		}
		tmp_ptr++;
	}

	write(1, "\n", 1);
	print_horizontal_bar(nmemb);
	write(1, "\n", 1);
}

void print_horizontal_bar(unsigned long int n)
{
	unsigned long int i;

	for (i = 0; i < n * 5; i++)
	{
		write(1, "-", 1);
	}
}

/* see ~memset(3)~ */
void _memset(void *s, int c, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		*((char *) s + i) = c;
	}
}

int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; i < n - 1; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
		{
			break;
		}

		if (s1[i] != s2[i]) /* if chars are different, break */
		{
			break;
		}
	}

	return(s1[i] - s2[i]); /* return difference in chars */
}

void print_grid(char **grid)
{
	int i;

	for (i = 0; grid[i] != NULL; i++)
	{
		print_string(grid[i]);
		print_char('\n');
	}
}

void print_string(char *s)
{
	while (*s != '\0')
	{
		print_char(*s);
		s++;
	}
}

int _strlen(char *str)
{
	int i;			/* i used as a counter */

	i = 0;			/* initialize at 0 */

        /* while string isn't over */
	while (*str != '\0') {
		i++;		/* increase counter */
		str++;		/* pointer arithmetic for next char */
	}

	return (i);
}

char *_strcat(char *dest, const char *src)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0';

	return (dest);
}

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	i++;
	dest[i] = '\0';

	return (dest);
}

/* on error, returns NULL */
char *_strdup(char *str)
{
	int i, length;
	char *str2; 			/* hold the second string */

	for (i = 0; *str != '\0'; i++) /* get the length */
	{
		str++;
	}

	length = i;

	str = str - length; 		/* pointer arithmetic to first element */

	str2 = malloc( sizeof(char) * (length + 1) ); /* assign the memory */

	if (str2 == NULL)	/* check the memory */
	{
		perror("strdup");
		return (NULL);
	}

	for (i = 0; i <= length; i++)	/* copy null char as well */
	{
		*str2 = *str; 		/* copy char */
		str++;			/* increase */
		str2++;			/* char */
	}

	return str2 - length - 1; 	/* return the pointer */
}

void canary()
{
	static int i = 0;

	if (DEBUG)
	{
		i++;
		printf("---%d---\n", i);
	}
}
