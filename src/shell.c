#include "../headers/header.h"

int main(int __attribute__ ((unused)) argc, char *argv[], char **env)
{
	FILE *fp = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *cmd = NULL;
	int interactive;

	fp = stdin;

	interactive = _isinteractive();

	while (1)
	{
		if (interactive)
		{
			print_prompt();
		}

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
			canary("exec begins");

			/**
			 * PROGRAM EXEC
			 * fork() begins here
			 */

			if (handle_exec(cmd, line, env))
			{
				canary("hello");
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

	int exitn, arglen;
	char *arg = NULL;

	/* printf("%lu\n", read); */

	if (_strncmp(cmd, "exit", 5) == 0)
	{
		arg = strtok(NULL, " \n");
		if (arg != NULL)
		{
			arglen = _strlen(arg);
			if (valid_exitarg(arg, arglen) == 1)
			{
				exitn = _atoin(arg, arglen);
				_free(line);
				exit(exitn);
			}
			print_string("exit: Illegal number\n");
			return (0);
		}
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

int _atoin(const char *s, int len)
{
	/* declarations */
	int i, base, res, digit;

	/* inits */
	res = 0;
	base = 1;

	for (i = 0; i < len; i++)
	{
		digit = s[len - i - 1] - 48;
		res += digit * base;
		base = base * 10;
	}

	return (res);
}

void _free(char *line)
{
	free(line);
	line = NULL;
}

/**
 * get_fpath - Looks for program in PATH.
 *
 * @cmd: program to search for
 * @env: environment context
 *
 * Return: if program found in PATH, returns a string specifying full path to
 * program. Otherwise, returns ~cmd~ unchanged (for relative path.). On memory
 * error, returns NULL.
 */
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

int _strlen(const char *str)
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

void canary(const char *s)
{
	static int i = 0;

	if (DEBUG)
	{
		i++;
		printf("---%d---\n", i);
		puts(s);
		printf("-------\n");
	}
}

/* returns 1 if interactive, 0 if pipe */
int _isinteractive()
{
	struct stat st;

	if (fstat(0, &st) == -1)
	{
		perror("fstat");
		exit(EXIT_FAILURE);
	}

	if (S_ISFIFO(st.st_mode))
	{
		canary("pipe");
		return (0);
	}

	canary("not pipe");
	return (1);
}

int valid_exitarg(char *arg, int len)
{
	int i;

	for (i = 0; i < len; i++)
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			return (0);
		}
	}

	return (1);
}
