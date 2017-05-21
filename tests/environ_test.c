#include "../header.h"
#include <unistd.h>

/* gcc -g -Wall -Wextra -Werror -pedantic environ_test.c ../print_grid.c ../print_char.c ../string.c ../print_func.c && ./a.out */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
	 char **env)
{
	int i;
	unsigned long int diff;

	/* print_grid(env); */

	for (i = 0; env[i + 1] != NULL; i++)
	{
		printf("address env[%d]: %p\n", i, (void *) env[i]);
		diff = env[i + 1] - env[i];
		printf("diff: %lu\t", (unsigned long) diff);
		printf("env[%d]: %s\t", i, env[i]);
		printf("strlen + 1: %d\n", _strlen(env[i]) + 1);
	}
	printf("\t\tenv[%d]: %s\n", i, env[i]);
	printf("\t\tenv[%d]: %s\n", i + 1, env[i + 1]);

	return (0);
}
