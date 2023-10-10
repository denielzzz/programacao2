all: A3.o enemy.o space.o
	gcc -o A3 A3.o enemy.o space.o

A3.o: A3.c
	gcc -Wall -Wextra -g -c A3.c

enemy.o: enemy.c
	gcc -Wall -Wextra -g -c enemy.c

space.o: space.c
	gcc -Wall -Wextra -g -c space.c

clean:
	rm -f *.o A3