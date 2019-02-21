# Script
# Compila y crea ejecutable:
# p1_e2

#################################
#! /bin/bash
gcc -g -Wall -pedantic -ansi -std=c99 -c node.c
gcc -g -Wall -pedantic -ansi -std=c99 -c graph.c
gcc -g -Wall -pedantic -ansi -std=c99 -c p1_e2.c
gcc -g -Wall -pedantic -ansi -std=c99 -o p1_e2 p1_e2.o node.o graph.o
valgrind --leak-check=full ./p1_e2
#################################
