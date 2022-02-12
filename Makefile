# generic makefile for c projects
# compiles and links all .c files to the name specified in EXEC

EXEC = mylang

CC = gcc
CFLAGS = -c -Wall -pedantic -O0 -g -DDEBUG
LDFLAGS =

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))  # .o filenames for all .c files

all: $(EXEC)

$(EXEC): $(OBJECTS)  # link all .o to EXEC
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c  # compile a .c file to .o
	$(CC) $(CFLAGS) -o $@ $<

clear: clean
	rm -f $(EXEC)

clean:
	rm -f *.o

.PHONY: clear, clean