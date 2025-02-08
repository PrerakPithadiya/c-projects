CC = gcc
CFLAGS = -I../include
DEPS = ../include/sudoku_solver.h ../include/progress_bar.h ../include/number_guessing_game.h ../include/kaun_banega_crorepati.h ../include/digital_clock.h ../include/bank_management_system.h
OBJ = test_sudoku_solver.o test_progress_bar.o test_number_guessing_game.o test_kaun_banega_crorepati.o test_digital_clock.o test_bank_management_system.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_sudoku_solver: test_sudoku_solver.o
	$(CC) -o $@ $^ $(CFLAGS)

test_progress_bar: test_progress_bar.o
	$(CC) -o $@ $^ $(CFLAGS)

test_number_guessing_game: test_number_guessing_game.o
	$(CC) -o $@ $^ $(CFLAGS)

test_kaun_banega_crorepati: test_kaun_banega_crorepati.o
	$(CC) -o $@ $^ $(CFLAGS)

test_digital_clock: test_digital_clock.o
	$(CC) -o $@ $^ $(CFLAGS)

test_bank_management_system: test_bank_management_system.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o test_sudoku_solver test_progress_bar test_number_guessing_game test_kaun_banega_crorepati test_digital_clock test_bank_management_system
