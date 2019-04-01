########################################################
# Argumentos:
# FILE: (nodos.txt) archivo de texto
# FROM: ID del nodo origen para p3_e1
# TO: ID del nodo destino para p3_e1
#
# EJEMPLO: make run1 FILE=g2_s.txt FROM=33 TO=7
########################################################

CC = gcc
CFLAGS = -g -Wall -ansi -std=c99 -pedantic
EJS = p3_e1 p3_test

########################################################
OBJECTS = node.o queue.o
########################################################

all: $(EJS)

p3_e1: $(OBJECTS) p3_e1.o graph.o eleint.o
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTS) p3_e1.o graph.o eleint.o

p3_test: $(OBJECTS) p3_testqueue.o
	$(CC) $(CFLAGS) -o p3_test $(OBJECTS) p3_testqueue.o

####

p3_e1.o: p3_e1.c queue.h node.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_testqueue.o: p3_testqueue.c queue.h node.h
	$(CC) $(CFLAGS) -c p3_testqueue.c

####

eleint.o: eleint.c eleint.h
	$(CC) $(CFLAGS) -c eleint.c

graph.o: graph.c graph.h queue.h eleint.h
	$(CC) $(CFLAGS) -c graph.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

####

clear:
	rm -rf *.o
	rm $(EJS)

####

run1:
	valgrind --leak-check=full ./p3_e1 $(FILE) $(FROM) $(TO)

run2:
	valgrind --leak-check=full ./p3_test $(FILE)
