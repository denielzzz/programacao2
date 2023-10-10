all : main.o deck.o
	gcc main.o deck.o -o main

main.o : main.c
	gcc -c main.c

deck.o : deck.c
	gcc -c deck.c

clean :
	rm main *.o