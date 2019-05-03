#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c cadena.c
gcc -g -Wall -ansi -std=c99 -pedantic -c tree.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p4_e4.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p4_e4 tree.o p4_e4.o cadena.o

rm -rf *.o

cat strings.txt
valgrind --leak-check=full ./p4_e4 "strings.txt"
