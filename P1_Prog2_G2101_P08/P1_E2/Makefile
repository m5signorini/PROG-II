########################################################
CC = gcc
CFLAGS = -g -Wall -pedantic
EJS = p1_e2
########################################################
OBJECTSE2 = p1_e2.o node.o graph.o
########################################################
all: $(EJS) clear

p1_e2: $(OBJECTSE2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSE2)

####

p1_e2.o: p1_e2.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e2.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c node.h graph.h
	$(CC) $(CFLAGS) -c graph.c

clear:
	rm -rf *.o
