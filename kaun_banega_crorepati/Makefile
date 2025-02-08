CC = gcc
CFLAGS = -Iinclude
DEPS = include/kaun_banega_crorepati.h
OBJ = src/kaun_banega_crorepati.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kaun_banega_crorepati: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o kaun_banega_crorepati
