#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c queue.c
gcc -g -Wall -ansi -std=c99 -pedantic -c graph.c
gcc -g -Wall -ansi -std=c99 -pedantic -c eleint.c
gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p3_e1.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p3_e1 p3_e1.o node.o queue.o graph.o eleint.o

rm -rf *.o

valgrind --leak-check=full ./p3_e1 g2_s.txt 33 7
