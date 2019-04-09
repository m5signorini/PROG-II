#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c list.c
gcc -g -Wall -ansi -std=c99 -pedantic -c eleint.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p3_e2.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p3_e2 p3_e2.o eleint.o list.o

rm -rf *.o

valgrind --leak-check=full ./p3_e2 15
