#include "header.h"

void print_buffer(void *ptr, size_t nmemb)
{
	unsigned long int i;
	char *tmp_ptr;

	tmp_ptr = ptr;

	print_horizontal_bar(nmemb);
	write(1, "\n", 1);

	write(1, "|", 1);
	for (i = 0; i < nmemb; i++)
	{
		write(1, " ", 1);
		if (*tmp_ptr == 10)
		{
			write(1, "\\n", 2);
		} else {
			write(1, tmp_ptr, 1);
		}
		write(1, " |", 3);
		tmp_ptr++;
	}

	write(1, "\n", 1);
	print_horizontal_bar(nmemb);

	tmp_ptr = ptr;

	write(1, "\n", 1);
	write(1, "|", 1);
	for (i = 0; i < nmemb; i++)
	{
		if (*tmp_ptr == 10)
		{
			printf("%3d |", *tmp_ptr);
			fflush(stdout);
		} else {
			printf("%3d|", *tmp_ptr);
			fflush(stdout);
		}
		tmp_ptr++;
	}

	write(1, "\n", 1);
	print_horizontal_bar(nmemb);
	write(1, "\n", 1);
}

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
