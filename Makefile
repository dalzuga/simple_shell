all:
	gcc -Wall -Werror -Wextra -pedantic src/*.c -o shell
run:
	valgrind --leak-check=full --track-origins=yes --leak-check=full --show-leak-kinds=all ./shell
clean:
	rm shell
