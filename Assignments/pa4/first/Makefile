first: runSim.o validate.o first.c
	gcc -Wall -Werror -fsanitize=address first.c runSim.o validate.o -o first

runSim.o: runSim.c runSim.h
	gcc -Wall -Werror -fsanitize=address -c runSim.c

validate.o: validate.c validate.h
	gcc -Wall -Werror -fsanitize=address -c validate.c

clean:
	rm -rf *.o first *.exe
