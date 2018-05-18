CC=gcc
CFLAGS=-std=c99 -W -Wall -ansi -pedantic
LDFLAGS= -lm
EXEC=mybot

all: $(EXEC)

mybit: mybot.o
	$(CC) -o mybot mybot.o $(LDFLAGS)


main.o: Sergefinal.c Sergefinal.h
	$(CC) -o mybot.o -c Sergefinal.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
