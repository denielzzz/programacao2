all : main.o libFila.o
	gcc -o main main.o libFila.o

main.o : main.c
	gcc -g -Wall -Wextra -c main.c

libFila.o : libFila.c
	gcc -g -Wall -Wextra -c libFila.c

clean :
	rm main *.o