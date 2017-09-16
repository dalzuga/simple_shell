#include "header.h"

int _unsetenv(char ***env)
{
	int i;

	/* declarations */
	char *envvar;

	envvar = strtok(NULL, " \n");
	if (envvar == NULL)
	{
		print_error("missing argument\n");
		return (1);
	}

	for (i = 0; (*env)[i] != NULL; i++)
	{
		if (_strncmp((*env)[i], envvar, _strlen(envvar) + 1) == 0)
		{
			printf("found: %s\n", (*env)[i]);
			return (0);
		}
	}

	printf("not found\n");
	printf("query: %s\n", envvar);
	return (0);
}
