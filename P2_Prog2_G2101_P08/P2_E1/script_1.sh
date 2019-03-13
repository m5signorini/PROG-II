#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c stack_elestack.c
gcc -g -Wall -ansi -std=c99 -pedantic -c elestack-node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p2_e1.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p2_e1 node.o stack_elestack.o elestack-node.o p2_e1.o

rm -rf *.o

valgrind --leak-check=full ./p2_e1
