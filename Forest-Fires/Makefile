CC=gcc
#CFLAGS=-Wall -Wextra -pedantic -std=c90 -O3
CFLAGS=-Wall -Wextra -pedantic -std=c90 -g3 -fsanitize=undefined -fsanitize=address
LDLIBS= -lm

forest : neillsimplescreen.c neillsimplescreen.h forest.c
	$(CC) forest.c neillsimplescreen.c -o forest $(CFLAGS) $(LDLIBS)

demo_neillncurses : neillncurses.c neillncurses.h demo_neillncurses.c
	$(CC) demo_neillncurses.c neillncurses.c -o demo_neillncurses $(CFLAGS) $(LDLIBS) -lncurses
