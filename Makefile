LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lncursesw
CFLAGS = -Wall -g -I/mingw64/include/SDL2 -I/mingw64/include/ncursesw
CC = gcc

all: tracker

tracker: main.o chip.o gui.o input_lib.o event_handler.o input_processing.o input_event.o input_utils.o action_reaction.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c stuff.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tracker

.PHONY: all clean
