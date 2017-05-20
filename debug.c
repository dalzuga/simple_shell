#include "header.h"

void canary(const char *s)
{
	static int i = 0;

	if (DEBUG)
	{
		i++;
		printf("---%d---\n", i);
		puts(s);
		printf("-------\n");
	}
}
