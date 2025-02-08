CC = gcc
CFLAGS = -Iinclude
DEPS = include/progress_bar.h
OBJ = src/progress_bar.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

progress_bar: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o progress_bar
