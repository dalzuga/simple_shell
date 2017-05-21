#include "header.h"

/**
 * _setenv - set an environment variable
 *
 * @env: the current environment
 *
 * Return: 0 on success, 1 otherwise.
 */
int _setenv(char **env)
{
	/* declarations */
	char *envvar, *envval;

	envvar = strtok(NULL, " ");
	if (envvar == NULL)
	{
		perror("missing argument");
		return (1);
	}

	envval = strtok(NULL, " ");
	if (envval == NULL)
	{
		perror("missing value");
		return (1);
	}

	return (_setenv_func(env, envvar, envval));
}

/**
 * _setenv_func - helper to _setenv
 *
 * @env: the current environment
 * @envvar: variable name
 * @envval: variable value
 *
 * Return: 0 on success, 1 otherwise.
 */
int _setenv_func(char **env, char *envvar, char *envval)
{
	/* declarations */
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		/* variable exists */
		if (_cstrcmp(env[i], envvar) == 0)
		{
			free(env[i]);
			env[i] = new_path_str(envvar, envval);
			return (0);
		}
	}

	/* variable does not exist */
	env[i] = new_path_str(envvar, envval);
	env[++i] = NULL;

	return (0);
}
