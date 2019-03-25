########################################################
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99 -pedantic
EJS = p2_e2
########################################################
OBJECTSE2 = p2_e2.o stack_elestack.o elestack-int.o
########################################################
all: $(EJS) clear

p2_e2: $(OBJECTSE2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSE2)

####

p2_e2.o: p2_e2.c stack_elestack.h
	$(CC) $(CFLAGS) -c p2_e2.c

####

stack_elestack.o: stack_elestack.h
	$(CC) $(CFLAGS) -c stack_elestack.c

elestack-int.o: elestack.h
	$(CC) $(CFLAGS) -c elestack-int.c

####

clear:
	rm -rf *.o

####

run:
	valgrind --leak-check=full ./p2_e2 7
