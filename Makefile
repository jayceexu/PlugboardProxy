CC=gcc
CFLAGS=-g -Wall 
LIBS=-lpthread -lcrypto
pbproxy: pbproxy.o
	$(CC) -o pbproxy pbproxy.o $(CFLAGS) $(LIBS)


.PHONY: clean
clean:
	rm -f *.o pbproxy