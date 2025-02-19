LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lncursesw
CFLAGS = -Wall -I/mingw64/include/SDL2 -I/mingw64/include/ncursesw
CC = gcc

all: tracker

tracker: main.o chip.o gui.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c stuff.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tracker

.PHONY: all clean
