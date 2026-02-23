CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native -funroll-loops -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

clean:
	rm -f src/*.o main