all:
	gcc -Wall -Werror -Wextra -pedantic *.c -o shell
g:
	gcc -g -Wall -Werror -Wextra -pedantic *.c -o shell
g3:
	gcc -g3 -Wall -Werror -Wextra -pedantic *.c -o shell
run:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./shell
clean:
	rm shell
