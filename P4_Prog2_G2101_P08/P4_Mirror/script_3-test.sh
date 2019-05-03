#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c tree.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p4_test-node-tree.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p4_test-node-tree tree.o p4_test-node-tree.o node.o

rm -rf *.o

cat nodos.txt
valgrind --leak-check=full ./p4_test-node-tree "nodos.txt"
