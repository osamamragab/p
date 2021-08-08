CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O2

SRC = p.c
OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) -c $(CFLAGS) $<

p: $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -f p $(OBJ)

.PHONY: clean
