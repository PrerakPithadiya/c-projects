CC = gcc
CFLAGS = -Iinclude
DEPS = include/digital_clock.h
OBJ = src/digital_clock.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

digital_clock: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o digital_clock
