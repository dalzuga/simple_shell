#include "../header.h"

/*
 * To compile, from root directory:
 * gcc -g -Wall -Wextra -Werror -pedantic tests/new_path_string_test.c string.c print_func.c print_char.c debug.c
 */

/* new string with format "variable" + '=' + "value", like in PATH */
char *new_path_str(char *envvar, char* envval)
{
	int envvar_len, envval_len, path_len = 0;
	char *path_str;

	envvar_len = _strlen(envvar);
	envval_len = _strlen(envval);

	/* '=' + '\0' --> 2 additional chars */
	path_len = envvar_len + envval_len + 2;

	path_str = malloc(sizeof(char) * (path_len));
	if (path_str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	_memset(path_str, '\0', path_len);
	path_str = _strcat(path_str, envvar);
	path_str = _strcat(path_str, "=");
	path_str = _strcat(path_str, envval);

	return (path_str);
}

int main()
{
	print_buffer(new_path_str("hi", "there"), 9);

	return 0;
}
