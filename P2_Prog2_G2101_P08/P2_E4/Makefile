########################################################
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99 -pedantic
EJS = p2_e4
########################################################
OBJECTSE4 = p2_e4.o stack_fp.o graph.o node.o eleint.o
########################################################
all: $(EJS) clear

p2_e4: $(OBJECTSE4)
	$(CC) $(CFLAGS) -o p2_e4 $(OBJECTSE4)

####

p2_e4.o: p2_e4.c node.h graph.h
	$(CC) $(CFLAGS) -c p2_e4.c

####

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c node.h graph.h stack_fp.h eleint.h
	$(CC) $(CFLAGS) -c graph.c

stack_fp.o: stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c stack_fp.c

eleint.o: eleint.c
	$(CC) $(CFLAGS) -c eleint.c

####

clear:
	rm -rf *.o

####

run:
	valgrind --leak-check=full ./p2_e4 "g2_s.txt" 33 7
