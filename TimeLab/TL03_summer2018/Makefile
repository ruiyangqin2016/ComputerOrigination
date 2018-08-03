CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror -Wextra
DEBUG_FLAGS = -g -DDEBUG

run-test : build-debug
	./test

run-gdb : build-debug
	gdb ./test

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./test

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : llist.o test.o llist.h
	$(CC) $(CFLAGS) test.o llist.o -o test

llist.o : llist.c llist.h
	$(CC) $(CFLAGS) -c llist.c

test.o : test.c llist.h
	$(CC) $(CFLAGS) -c test.c

clean :
	rm *.o test

submit :
	tar -czvf tl03_submission.tar.gz llist.c llist.h test.c Makefile

