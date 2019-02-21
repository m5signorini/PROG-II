# Script
# Compila y crea ejecutable:
# p1_e1

#################################
#! /bin/bash
p1_e1 clear

gcc -g -Wall -pedantic -ansi -std=c99 -c node.c
gcc -g -Wall -pedantic -ansi -std=c99 -c p1_e1.c
gcc -g -Wall -pedantic -ansi -std=c99 -o p1_e1 p1_e1.o node.o

rm -rf *.o

valgrind --leak-check=full ./p1_e1
#################################
