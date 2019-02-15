# Comentario
# Archivo .sh run in linux
#
#! /bin/bash

#gcc -g node.c
#gcc -g p1_e1.c
#gcc -o ejecutable p1_e1.o node.o
gcc -g node.c graph.c p1_e3.c -o ejecutable

valgrind --leak-check=full --show-leak-kinds=all ./ejecutable g1.txt
