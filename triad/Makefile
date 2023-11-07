CC = gcc
CFLAGS = -O3 -march=native -Wall -Wextra -Werror -fno-tree-vectorize
TARGET = triad

$(TARGET): triad.c
	$(CC) $(CFLAGS) -o $(TARGET) triad.c

.PHONY: clean
clean:
	rm -f $(TARGET)
