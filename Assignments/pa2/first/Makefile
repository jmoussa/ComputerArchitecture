all:
	gcc -Wall -Werror -fsanitize=address first.c -o first

first: first.c
	gcc -Wall -Werror -fsanitize=address first.c -o first

clean:
	rm -rf first
	
debug: 
	gcc -Wall -Werror -fsanitize=address first.c -g -o first
