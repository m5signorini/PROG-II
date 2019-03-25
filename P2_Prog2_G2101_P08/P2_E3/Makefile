########################################################
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99 -pedantic
EJS = p2_e3
########################################################
OBJECTSE3 = p2_e3.o stack_fp.o node.o eleint.o
########################################################
all: $(EJS) clear

p2_e3: $(OBJECTSE3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSE3)

####

p2_e3.o: p2_e3.c node.h stack_fp.h eleint.h
	$(CC) $(CFLAGS) -c p2_e3.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

stack_fp.o: stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c stack_fp.c

eleint.o: eleint.c
	$(CC) $(CFLAGS) -c eleint.c

####

clear:
	rm -rf *.o

####

run:
	valgrind --leak-check=full ./p2_e3 7
