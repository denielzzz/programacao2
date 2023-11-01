CC = gcc
LIBS = `pkg-config allegro-5 allegro_primitives-5 --libs --cflags`
FILES = spaceInvaders.c ship.c map.c enemy.c obstacle.c shot.c
EXEC = game

all: $(FILES)
	$(CC) $(FILES) -o $(EXEC) $(LIBS) 

clean:
	rm -f $(EXEC)
