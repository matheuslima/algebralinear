#include <stdio.h>
#include "gaussJordan.h"
#include "matrizes.h"
void imprimirMatrizQuadrada(int dimensao, double** matriz);
void imprimirMatrizAumentada(int dimensao, double** matriz);

int main(void)
{
    double Matriz[2][2] = {{4,3},{8,7}};
    double **pMatriz = NULL;
    double **pMatrizInversa = NULL;
    double **pMatrizTransposta = NULL;
    int i,j;

    pMatriz = (double**)malloc(2*sizeof(double*));
    if(pMatriz == NULL) return -1;
    for(i = 0; i < 2; i++)
    {
        pMatriz[i] = (double*) malloc(2*sizeof(double));
    }
    for(i = 0; i < 2; i++)
        for(j = 0; j < 2; j++)
            pMatriz[i][j] = Matriz[i][j];

    pMatrizInversa = criarMatrizInversa(2, pMatriz);
    pMatrizTransposta = transposto(pMatriz, 2, 2);
    printf("Matriz original\n");
    imprimirMatrizQuadrada(2, pMatriz);
    printf("Matriz inversa\n");
    imprimirMatrizQuadrada(2, pMatrizInversa);
    printf("Matriz transposta\n");
    imprimirMatrizQuadrada(2, pMatrizTransposta);
    // desalocacoes
    for(i = 0; i < 2; i++)
    {
        free(pMatriz[i]);
        pMatriz[i] = NULL;
    }
    free(pMatriz);
    pMatriz = NULL;
    return 0;
}

void imprimirMatrizQuadrada(int dimensao, double** matriz)
{
    int i,j;
    if(matriz == NULL) return;
    for(i = 0; i < dimensao; i++)
    {
        for(j = 0; j < dimensao; j++)
            printf("%f\t", matriz[i][j]);
        printf("\n");
    }
}
