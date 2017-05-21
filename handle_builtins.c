#include "header.h"

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

	if (_strncmp(cmd, "#", 1) == 0)
	{
		return (0);
	}

	return (1);
}
