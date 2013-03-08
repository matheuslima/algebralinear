#ifndef MATRIZES_H
#define MATRIZES_H

// Implementacao de funcoes gerais para manipulacao de matrizes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Efetua o produto entre duas matrizes A e B, desde que suas dimensoes
// sejam MxN e NxP respectivamente.
double** produto(double** matrizA, int linhasA, int colunasA, double** matrizB, int linhasB, int colunasB);

// Obtem o transposto de uma matriz
double** transposto(double** matriz, int linhas, int colunas);

#endif
