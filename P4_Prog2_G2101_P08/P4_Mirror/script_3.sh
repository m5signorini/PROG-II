#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c tree.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p4_e3.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p4_e3 tree.o p4_e3.o node.o

rm -rf *.o

./p4_e3 "dict1M.dat" B

./p4_e3 "dict1M.dat" N

