# Script
# Compila y crea ejecutable:
# p1_e1

#################################
#! /bin/bash
gcc -c node.c
gcc -c p1_e1.c
gcc -o p1_e1 p1_e1.o node.o
./p1_e1
#################################

# Usando valgrind
gcc -g node.c p1_e1.c -o p1_e1
valgrind --leak-check=full ./p1_e1
