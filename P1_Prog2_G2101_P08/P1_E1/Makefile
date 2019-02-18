########################################################
CC = gcc
CFLAGS = -g -Wall -pedantic
EJS = p1_e1
########################################################
OBJECTSE1 = p1_e1.o node.o
########################################################
all: $(EJS) clear

p1_e1: $(OBJECTSE1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSE1)

####

p1_e1.o: p1_e1.c node.h
	$(CC) $(CFLAGS) -c p1_e1.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

clear:
	rm -rf *.o
