CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c src/shell.c
OUT = shell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) *.o
