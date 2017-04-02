#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "header.h"

int main()
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	stream = stdin;

	while (1)
	{
		print_prompt();
		read = getline(&line, &len, stream);

		if (stream == NULL)
		{
			/* if stream is a file which failed to open */
			return (EXIT_FAILURE);
		}

		/* handle EOF */
		if (read == -1)
		{
			free(line);

			if (errno == 0)
			{
				return (EXIT_SUCCESS);
			}

			perror("Something went wrong. errno is not 0.");
			return (EXIT_FAILURE);
		}

		printf("Read: %d\n", (int) read);
		printf("%s", line);
	}

	return (EXIT_SUCCESS);
}
