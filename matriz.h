#ifndef MATRIZES_H
#define MATRIZES_H

// Implementacao de funcoes gerais para manipulacao de matrizes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

// Estrutura para abstrair uma matriz
typedef struct{
    double** conteudo; // elementos da matriz
    int linhas; // numero de linhas da matriz
    int colunas; // numero de colunas da matriz
}Matriz;

// Macro para verificar se uma matriz eh quadrada
#define MATRIZ_QUADRADA(matriz)(matriz->linhas == matriz->colunas)

// Efetua a alocacao de uma matriz a partir da especificacao de suas dimensoes.
// Todos os seus elementos sao inicializados com zero
Matriz* criarMatriz(int linhas, int colunas);

// Cria uma matriz aumentada de dimensao N x 2N a partir da matriz quadrada passada.
// Essa matriz consiste da matriz passada como parametro ao lado da matriz identidade
// de dimensao N
Matriz* criarMatrizAumentada(Matriz* matriz, Status *status);

// Efetua a combinacao linear entre dois vetores:
// a*X + b*Y
double* combinacaoLinear(double* X, double* Y, double a, double b, int tamanho);

// Desaloca a matriz
void destruirMatriz(Matriz* matriz);

// Efetua o produto entre duas matrizes A e B, desde que suas dimensoes
// sejam MxN e NxP respectivamente.
Matriz* produto(Matriz matrizA, Matriz matrizB);

// Obtem o transposto de uma matriz
Matriz* transposto(Matriz matriz);

#endif
