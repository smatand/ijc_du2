LC_ALL=cs_CZ.utf8

FLAGS = -pedantic -std=c11 -g -Wall -Wextra
CC = gcc
EXECUTABLES = tail

all: $(EXECUTABLES)

tail.o: tail.c
	$(CC) $(FLAGS) -c tail.c -o tail.o

tail: tail.o
	$(CC) $(FLAGS) tail.o -o tail

archive:
	zip xsmata03.zip *.c *.h Makefile
clean: 
	rm -f *.o $(EXECUTABLES)
