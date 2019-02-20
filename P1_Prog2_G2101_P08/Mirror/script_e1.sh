# Script
# Compila y crea ejecutable:
# p1_e1

#################################
#! /bin/bash
p1_e1 clear

gcc -g -Wall -ansi -pedantic -c node.c
gcc -g -Wall -ansi -pedantic -c p1_e1.c
gcc -g -Wall -ansi -pedantic -o p1_e1 p1_e1.o node.o

rm -rf *.o

valgrind --leak-check=full ./p1_e1
#################################

# Usando valgrind
# gcc -g node.c p1_e1.c -o p1_e1
# valgrind --leak-check=full ./p1_e1
