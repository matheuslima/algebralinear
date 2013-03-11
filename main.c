#include <stdio.h>
#include "gaussJordan.h"
#include "matriz.h"
void imprimirMatriz(Matriz matriz);

int main(void)
{
    double matriz[3][3] = {{2,-1,0},{-1,2,-1},{0,-1,2}};
    Matriz *pMatriz = NULL;
    Matriz *pMatrizInversa = NULL;
    Matriz *pMatrizTransposta = NULL;
    int i,j;

    pMatriz = criarMatriz(3,3);
    if(pMatriz == NULL) return -1;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            pMatriz->conteudo[i][j] = matriz[i][j];
    pMatriz->linhas = 3;
    pMatriz->colunas = 3;

    pMatrizInversa = criarMatrizInversa(pMatriz);
    pMatrizTransposta = transposto(*pMatriz);

    printf("Matriz original\n");
    imprimirMatriz(*pMatriz);
    printf("Matriz inversa\n");
    imprimirMatriz(*pMatrizInversa);
    printf("Matriz transposta\n");
    imprimirMatriz(*pMatrizTransposta);
    // desalocacoes
    destruirMatriz(pMatriz);
    destruirMatriz(pMatrizTransposta);
    destruirMatriz(pMatrizInversa);
    return 0;
}

void imprimirMatriz(Matriz matriz)
{
    int i,j;
    for(i = 0; i < matriz.linhas; i++)
    {
        for(j = 0; j < matriz.colunas; j++)
            printf("%f\t", matriz.conteudo[i][j]);
        printf("\n");
    }
}
