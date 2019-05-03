#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c eleint.c
gcc -g -Wall -ansi -std=c99 -pedantic -c tree.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p4_e1.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p4_e1 tree.o p4_e1.o eleint.o

rm -rf *.o

cat numeros.txt
valgrind --leak-check=full ./p4_e1 "numeros.txt"
