CC = gcc
CFLAGS = -Iinclude
DEPS = include/sudoku_solver.h
OBJ = src/sudoku_solver.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sudoku_solver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o sudoku_solver
