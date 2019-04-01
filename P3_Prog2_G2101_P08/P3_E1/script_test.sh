#!/bin/bash

gcc -g -Wall -ansi -std=c99 -pedantic -c queue.c
gcc -g -Wall -ansi -std=c99 -pedantic -c node.c
gcc -g -Wall -ansi -std=c99 -pedantic -c p3_testqueue.c
gcc -g -Wall -ansi -std=c99 -pedantic -o p3_test p3_testqueue.o node.o queue.o

rm -rf *.o

valgrind --leak-check=full ./p3_test nodos.txt
