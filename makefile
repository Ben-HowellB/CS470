CC = gcc
CFLAGS = -Wall -g

all: testfs

testfs: Ben_libFS.o Ben_testFS.o
	$(CC) $(CFLAGS) -o testfs Ben_libFS.o Ben_testFS.o

Ben_libFS.o: Ben_libFS.c Ben_libFS.h
	$(CC) $(CFLAGS) -c Ben_libFS.c

Ben_testFS.o: Ben_testFS.c Ben_libFS.h
	$(CC) $(CFLAGS) -c Ben_testFS.c

clean:
	rm -f *.o testfs *.txt
