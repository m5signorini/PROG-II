########################################################
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99 -pedantic
EJS = p2_e1
########################################################
OBJECTSE1 = node.o stack_elestack.o elestack-node.o p2_e1.o
########################################################
all: $(EJS) clear

p2_e1: $(OBJECTSE1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSE1)

####

p2_e1.o: p2_e1.c node.h stack_elestack.h
	$(CC) $(CFLAGS) -c p2_e1.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

stack_elestack.o: stack_elestack.h
	$(CC) $(CFLAGS) -c stack_elestack.c

elestack-node.o: elestack.h
	$(CC) $(CFLAGS) -c elestack-node.c

####

clear:
	rm -rf *.o

####

run:
	valgrind --leak-check=full ./p2_e1
