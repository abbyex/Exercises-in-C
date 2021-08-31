CC=gcc
COMMON= -I/usr/include/SDL2 -D_REENTRANT -O3 -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON)
LIBS = -lm -lSDL2

interp_s : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c interp.h interp_func.c interp.c
		$(CC) -c interp.c interp_func.c stack/stack.c SDL/mysdl.c $(SANITIZE) $(LIBS)

interp_v : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c interp.h interp_func.c interp.c
		$(CC) -c interp.c interp_func.c stack/stack.c SDL/mysdl.c $(VALGRIND) $(LIBS)

interp_flags : interp_v interp_s

parse_s : parse.h parse_func.c parse.c
		$(CC) parse.c parse_func.c -o parse_s $(SANITIZE) $(LIBS)

parse_v : parse.h parse_func.c parse.c
		$(CC) parse.c parse_func.c -o parse_v $(VALGRIND) $(LIBS)

parse_flags : parse_s parse_v

extension_s : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c ext.h ext_func.c ext.c
	$(CC) ext.c ext_func.c stack/stack.c SDL/mysdl.c -o extension $(SANITIZE) $(LIBS)

extension_v : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c ext.h ext_func.c ext.c
		$(CC) ext.c ext_func.c stack/stack.c SDL/mysdl.c -o extension $(VALGRIND) $(LIBS)

extension_flags : extension_v extension_s



interp : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c interp.h interp_func.c interp.c interp_flags
	$(CC) interp.c interp_func.c stack/stack.c SDL/mysdl.c -o interp $(PRODUCTION) $(LIBS)

parse : parse.h parse_func.c parse.c parse_s parse_v parse_flags
	$(CC) parse.c parse_func.c -o parse $(PRODUCTION) $(LIBS)

extension : stack/stack.h stack/stack.c SDL/mysdl.h SDL/mysdl.c ext.h ext_func.c ext.c extension_flags
	$(CC) ext.c ext_func.c stack/stack.c SDL/mysdl.c -o extension $(PRODUCTION) $(LIBS)

clean:
	rm -f parse_s parse_v parse interp_s interp_v interp extension_s extension_v extension interp.o interp_func.o mysdl.o stack.o
