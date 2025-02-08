CC = gcc
CFLAGS = -Iinclude
DEPS = include/bank_management_system.h
OBJ = src/bank_management_system.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bank_management_system: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o bank_management_system
