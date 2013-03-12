#ifndef FATORACAOLU_H
#define FATORACAOLU_H

#include "matriz.h"

// Implementacao do algoritmo LU de fatoracao de matrizes. Tal algoritmo
// consiste em escrever a matriz A na forma de uma produto de duas matrizes
// L e U:
//                   A = L*U
// Onde L eh uma matriz triangular inferior com todos os elementos da diagonal
// principal iguais a 1 e U eh uma matriz triangular superior

// Fatora a matriz A em duas matrizes, L e U. Passam-se como parametros
// um ponteiro para a Matriz A, um ponteiro que armazenara a matriz L e
// um ponteiro que armazenara a matriz U
void fatorarMatriz(Matriz* A, Matriz* L, Matriz* U);

#endif
