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

install: p
	mkdir -p $(DESTDIR)/bin
	cp -f p $(DESTDIR)/bin
	chmod 755 $(DESTDIR)/bin/p

uninstall:
	rm -f $(DESTDIR)/bin/p

.PHONY: clean install uninstall
