CC = gcc
HEADERS = morse.h gpio.h
SOURCES = morse.c gpio.c
OBJECTS = morse.o gpio.o

default: program

$(OBJECTS): $(SOURCES)
	gcc -c $(SOURCES)
program: program.c $(OBJECTS)
	gcc -c program.c $(OBJECTS) -o program
clean:
	-rm -f program.o
	-rm -f program
	-rm $(OBJECTS)

