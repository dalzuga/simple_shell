#include "header.h"

/**
 * new_path_str - new string with format "variable" + '=' + "value"
 *
 * @envvar: environment variable name
 * @envval: environment variable value
 *
 * Return: the new PATH string.
 */
char *new_path_str(char *envvar, char* envval)
{
	int envvar_len, envval_len;
	char *path_str;

	envvar_len = _strlen(envvar);
	envval_len = _strlen(envval);

	path_str = malloc(sizeof(char) * (envvar_len + envval_len + 2));
	if (path_str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	path_str = _strcat(path_str, envvar);
	path_str = _strcat(path_str, "=");
	path_str = _strcat(path_str, envval);

	return (path_str);
}
