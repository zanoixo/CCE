CC = gcc
CFLAGS = -O3 -Wall -Wextra -march=native
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = bin/engine

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build bin/engine