#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

// Implementacao do algoritmo Gauss-Jordan de inversao de matrizes.
// Seja "A" uma matriz quadrada. O processo de inversao usando o
// referido algoritmo eh feito usando os seguintes passos:
// 1) Obter umaa matriz aumentada a partir da matriz A. Esse passo
//    consistem em obter uma matriz A' da seguinte forma:
//                   A' = [A I]
//    onde I eh a matriz identidade.
// 2) Gerar uma matriz triangular superior. A matriz aumentada eh
//    manipulada com o meio de combinacoes lineares entre suas linhas
//    para obter uma matriz cujos elementos abaixo da diagonal sao
//    zero. Os elementos da diagonal principal da matriz quadrada
//    do lado esquerdo da matriz aumentada formam os pivos da matriz A
// 3) Escalonar a matriz aumentada. Agora, por meio de combinacoes
//    lineares entre as linhas da matriz triangular, sao zerados todos
//    os elementos acima dos pivos. A seguir divide-se cada linha por
//    seu pivo correspondente.
// 4) A matriz escalonada obtida pelo passo 3 esta agora na seguinte forma:
//                    [I Ai]
//    A matrix Ai eh a matriz inversa de A. Obtem-se a matriz inversa por
//    inspensao da matriz escalonada

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"
#include "matriz.h"

// Macro para verificar se uma matriz eh quadrada
#define MATRIZ_QUADRADA(matriz)(matriz->linhas == matriz->colunas)

// Efetua a combinacao linear entre dois vetores:
// a*X + b*Y
double* combinacaoLinear(double* X, double* Y, double a, double b, int tamanho);

// Cria uma matriz triangular superior a partir da matriz aumentada.
Matriz* criarMatrizTriangular(Matriz* matrizAumentada, Status *status);

// A partir da matriz triangular, verifica se a matriz original pode ser
// invertida. Isso eh feito analisando-se o produto dos pivos. Se ele for
// diferente de zero, a matriz eh invertivel, se nao for, ela nao eh invertivel.
bool verificarInvertibilidadeMatriz(Matriz* matrizTriangular);

// Cria uma matriz escalonada a partir da matriz triangular.
Matriz* criarMatrizEscalonada(Matriz* matrizTriangular, Status *status);

// Cria a matriz inversa usando o algortimo de GaussJordan
Matriz* criarMatrizInversa(Matriz* matriz);

#endif
