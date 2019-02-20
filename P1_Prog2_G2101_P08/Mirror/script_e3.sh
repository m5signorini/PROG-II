# Script
# Compila y crea ejecutable:
# p1_e3

#################################
#! /bin/bash
gcc -c node.c
gcc -c graph.c
gcc -c p1_e3.c
gcc -o p1_e3 p1_e3.o node.o graph.o
./p1_e3 g1.txt
#################################

# Usando valgrind
gcc -g node.c graph.c p1_e3.c -o p1_e3
valgrind --leak-check=full ./p1_e3 g1.txt
