CC = gcc
CFLAGS = -I../include
DEPS = ../include/number_guessing_game.h
OBJ = src/number_guessing_game.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

number_guessing_game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o number_guessing_game
