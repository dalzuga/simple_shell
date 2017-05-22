#include "../header.h"
#include <unistd.h>

/* gcc -g -Wall -Wextra -Werror -pedantic tests/environ_test2.c print_grid.c print_char.c string.c print_func.c && ./a.out */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
	 char **env)
{
	int i;
	int env_len;
	char **tmp_env;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	env_len = i;

	printf("env_len: %d\n", env_len);

	tmp_env = malloc(sizeof(char **) * (env_len + 1));

	for (i = 0; i < env_len; i++)
	{
		tmp_env[i] = _strdup(env[i]);
		if (tmp_env[i] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
	}

	tmp_env[i] = NULL;

	for (i = 0; i < env_len + 1; i++)
	{
		printf("tmp_env[%d]: %s\n", i, tmp_env[i]);
	}

	return (0);
}
