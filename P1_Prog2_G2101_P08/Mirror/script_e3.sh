# Script
# Compila y crea ejecutable:
# p1_e3

#################################
#! /bin/bash

gcc -g -Wall -pedantic -ansi -std=c99 -c node.c
gcc -g -Wall -pedantic -ansi -std=c99 -c graph.c
gcc -g -Wall -pedantic -ansi -std=c99 -c p1_e3.c
gcc -g -Wall -pedantic -ansi -std=c99 -o p1_e3 p1_e3.o node.o graph.o

rm -rf *.o

valgrind --leak-check=full ./p1_e3 g1.txt
#################################
