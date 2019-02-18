########################################################
CC = gcc
CFLAGS = -g -Wall -pedantic
EJS = p1_e3
########################################################
OBJECTSE3 = p1_e3.o node.o graph.o
########################################################
all: $(EJS) clear

p1_e3: $(OBJECTSE3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSE3)

####

p1_e3.o: p1_e3.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e3.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c node.h graph.h
	$(CC) $(CFLAGS) -c graph.c

clear:
	rm -rf *.o
