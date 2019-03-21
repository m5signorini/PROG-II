#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c stack_fp.c
gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c eleint.c
gcc -g -Wall -ansi -std=c99 -pedantic -c graph.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p2_e4.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p2_e4 stack_fp.o graph.o p2_e4.o node.o eleint.o

rm -rf *.o

valgrind --leak-check=full ./p2_e4 "g2_s.txt" 33 7
