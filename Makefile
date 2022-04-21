LC_ALL=cs_CZ.utf8

CFLAGS=-std=c11 -pedantic -fPIC -Wall -Wextra #-O2
#CFLAGS=-std=c11 -pedantic -fPIC -Wall -Wextra -DHASH_TEST
CC=gcc
EXECUTABLES=tail wordcount wordcount-dynamic

HTAB_H=htab.h htab_private.h
HTAB_O=htab_init.o htab_clear.o htab_free.o htab_find.o htab_lookup_add.o \
	htab_erase.o htab_for_each.o htab_size.o htab_bucket_count.o htab_resize.o \
	htab_hash_function.o

all: $(EXECUTABLES)

#EXECUTABLES
tail: tail.o
	$(CC) $(CLAGS) $^ -o $@

#static version
wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static $^ -L. -lhtab -o $@
#dynamic version
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) $^ -o $@

libhtab.so: $(HTAB_O) $(HTAB_H)
	$(CC) $(CFLAGS) -shared $^ -o $@
libhtab.a: $(HTAB_O) $(HTAB_H)
	ar rcs $@ $^

#OBJECT FILES
tail.o: tail.c
	$(CC) $(CFLAGS) -c $^ -o $@
io.o: io.c io.h
	$(CC) $(CFLAGS) -c $^
wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $<


archive:
	zip xsmata03 *.h *.c Makefile
clean:
	rm -f *.o *.so *.a $(EXECUTABLES) *.gch
