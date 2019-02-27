#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c stack_elestack.c
gcc -g -Wall -ansi -std=c99 -pedantic -c elestack-int.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p2_e2.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p2_e2 stack_elestack.o elestack-int.o p2_e2.o

rm -rf *.o

valgrind --leak-check=full ./p2_e2 11
