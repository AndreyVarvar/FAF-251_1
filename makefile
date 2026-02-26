CC := gcc
LIBS := -lSDL3 -lm
CFLAGS := -Wall -Wextra -O3 -march=native -funroll-loops
BIN_NAME := sortificusmaximus


BUILD_DIR := build
SOURCE_DIR := src
SORTING_DIR := $(SOURCE_DIR)/sorting_algorithms

SRC := $(wildcard $(SOURCE_DIR)/*.c)
SRC_OBJ := $(SRC:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
SORTING_SRC := $(wildcard $(SORTING_DIR)/*.c)
SORTING_OBJ := $(SORTING_SRC:$(SORTING_DIR)/%.c=$(BUILD_DIR)/%.o)
ALL_OBJ :=  $(SORTING_OBJ) $(SRC_OBJ)

all: $(ALL_OBJ)
	$(CC) $(BUILD_DIR)/*.o -o $(BIN_NAME) $(LIBS)

$(BUILD_DIR)/%.o: $(SORTING_DIR)/%.c
	$(CC) -c $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -c $^ -o $@

run:
	./$(BUILD_DIR)/$(BIN_NAME) -m lskfjs

clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_NAME)
