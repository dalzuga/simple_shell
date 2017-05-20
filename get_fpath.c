#include "header.h"

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
