#include "header.h"

/* new string with format "variable" + '=' + "value", like in PATH */
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


int main()
{
	print_buffer(new_path_str("hi", "there"), 10);

	return 0;
}
