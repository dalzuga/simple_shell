#include "../header.h"

/* gcc -Wall -Werror -Wextra -pedantic ../string.c ../string2.c cstrcmp_test.c && ./a.out */

int main()
{
	char *s1, *s2;

	printf("----------\n");

	s1 = strdup("abc");
	s2 = strdup("abcde");
	printf("comparing: \"%s\" and \"%s\"\n", s1, s2);
	printf("result: %d\n", _cstrcmp(s1, s2));
	printf("expected: 0\n");

	printf("----------\n");

	s1 = strdup("aa");
	s2 = strdup("ab");
	printf("comparing: \"%s\" and \"%s\"\n", s1, s2);
	printf("result: %d\n", _cstrcmp(s1, s2));
	printf("expected: not 0\n");

	return (0);
}
