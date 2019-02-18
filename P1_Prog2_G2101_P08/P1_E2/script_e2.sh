# Script
# Compila y crea ejecutable:
# p1_e2

#################################
#! /bin/bash
gcc -c node.c
gcc -c graph.c
gcc -c p1_e2.c
gcc -o p1_e2 p1_e2.o node.o graph.o
./p1_e2
#################################

# Usando valgrind
gcc -g node.c graph.c p1_e2.c -o p1_e2
valgrind --leak-check=full ./p1_e2
