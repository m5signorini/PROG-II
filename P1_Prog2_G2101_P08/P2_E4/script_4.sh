#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c stack_fp.c
gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c graph.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p2_e4.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p2_e4 stack_fp.o graph.o p2_e4.o node.o

rm -rf *.o

valgrind --leak-check=full ./p2_e4 "g1.txt" 1 3
valgrind --leak-check=full ./p2_e4 "g1.txt" 1 2
valgrind --leak-check=full ./p2_e4 "g1.txt" 2 1
valgrind --leak-check=full ./p2_e4 "g1.txt" 2 3
valgrind --leak-check=full ./p2_e4 "g1.txt" 3 1
valgrind --leak-check=full ./p2_e4 "g1.txt" 3 2
