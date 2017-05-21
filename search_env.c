#include "header.h"

int search_env(char **env, int f)
{
	/* declarations */
	char *envvar, *envval;
	int i;

	envvar = strtok(NULL, " ");
	if (envvar == NULL)
	{
		perror("missing argument");
		return (0);
	}

	envval = strtok(NULL, " ");
	if (envval == NULL)
	{
		perror("missing value");
		return (0);
	}

	for (i = 0; env[i] != NULL; i++)
	{
		if (_cstrcmp(env[i], envvar) == 0)
		{

		}
	}

	if (f == 0)
	{
		return (newenv(envvar, envval, env));
	}

	return (delenv(envvar, envval, env));

}
