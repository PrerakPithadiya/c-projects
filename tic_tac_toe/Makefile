CC = gcc
CFLAGS = -Iinclude
DEPS = include/tic_tac_toe.h
OBJ = src/tic_tac_toe.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tic_tac_toe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o tic_tac_toe
