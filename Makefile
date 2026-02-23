CC = gcc
CFLAGS = -Wall -O2 -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

sortbench: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

clean:
	rm -f src/*.o main