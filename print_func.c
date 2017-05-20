#include "header.h"

void print_grid(char **grid)
{
	int i;

	for (i = 0; grid[i] != NULL; i++)
	{
		print_string(grid[i]);
		print_char('\n');
	}
}

void print_string(char *s)
{
	while (*s != '\0')
	{
		print_char(*s);
		s++;
	}
}


void print_horizontal_bar(unsigned long int n)
{
	unsigned long int i;

	for (i = 0; i < n * 5; i++)
	{
		write(1, "-", 1);
	}
}
