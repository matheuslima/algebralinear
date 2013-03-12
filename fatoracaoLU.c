#include "fatoracaoLU.h"

void fatorarMatriz(Matriz *A, Matriz *L, Matriz *U)
{
    int i,j,k;
    double* linha = NULL;
    double pivo, elemento;
    Status status;
    Matriz* matrizAumentada = NULL;

    if(A == NULL) return;
    if(!MATRIZ_QUADRADA(A)) return;

    matrizAumentada = criarMatrizAumentada(A, &status);

    if(matrizAumentada == NULL) return;

    // A partir da matriz aumentada, a fatoracao LU eh efetuada da
    // seguinte forma. Os elementos abaixo de um pivo sao todos zerados
    // por meio de combinacoes lineares entre as linhas da matriz
    // aumentada.
    for(i = 0; i < matrizAumentada->linhas - 1; i++)
        for(j = i + 1; j < matrizAumentada->linhas; j++)
        {
            pivo = matrizAumentada->conteudo[i][i];
            elemento = matrizAumentada->conteudo[j][i];
            if(elemento == 0) continue;
            linha = combinacaoLinear(matrizAumentada->conteudo[i],
                                     matrizAumentada->conteudo[j],
                                     -elemento/pivo,
                                     1,
                                     matrizAumentada->colunas);
            for(k = 0; k < matrizAumentada->colunas; k++)
                matrizAumentada->conteudo[j][k] = linha[k];
            free(linha);
        }

    // Cria novas matrizes para L e U
    *L = *criarMatriz(A->linhas, A->linhas);
    *U = *criarMatriz(A->linhas, A->linhas);

    // A partir da matriz aumentada, extrai-se a matriz U e a matriz L
    // A matriz U corresponde a metade esquerda da matriz aumentada e a
    // matriz L corresponde a metade direita da matriz aumentada
    for(i = 0; i < A->linhas; i++)
        for(j = 0; j < A->linhas; j++)
        {
            U->conteudo[i][j] = matrizAumentada->conteudo[i][j];
            L->conteudo[i][j] = matrizAumentada->conteudo[i][j+A->linhas];
        }
}
