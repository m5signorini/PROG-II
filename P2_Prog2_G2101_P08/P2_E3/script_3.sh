#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c stack_fp.c
gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c eleint.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p2_e3.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p2_e3 stack_fp.o eleint.o p2_e3.o node.o

rm -rf *.o

valgrind --leak-check=full ./p2_e3 3
