#include "header.h"

/**
 * _cstrcmp - cut string compare, meaning it will cut both strings to the
 * largest length of the two, and then perform the comparison.
 *
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if cut strings are equal, > 0 if s1 is lexicographically greater,
 * < 0 if smaller.
 */
int _cstrcmp(const char *s1, const char *s2)
{
	int i, s1_len, s2_len, s_len;

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);

	/* printf("s1_len: %d\n", s1_len); */
	/* printf("s2_len: %d\n", s2_len); */

	s_len = _min(s1_len, s2_len);

	/* printf("min: %d\n", s_len); */

	for (i = 0; i < s_len; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}

	return (0);
}

/* gives the max of two numbers */
int _max(int n, int m)
{
	if (n > m)
	{
		return n;
	}

	return m;
}

/* gives the min of two numbers */
int _min(int n, int m)
{
	if (n < m)
	{
		return n;
	}

	return m;
}

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
