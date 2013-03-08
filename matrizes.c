#include "matrizes.h"

double** produto(double **matrizA, int linhasA, int colunasA, double **matrizB, int linhasB, int colunasB)
{
    double** matrizProduto = NULL;
    int i,j,k;
    // Verifica se o produto pode ser feito. Isso ocorre se colunasA == linhasB
    bool produtoPossivel = colunasA == linhasB;
    if(!produtoPossivel) return NULL;

    matrizProduto = (double**) malloc(linhasA*sizeof(double*));
    if(matrizProduto == NULL) goto tratarErro;
    for(i = 0; i < linhasA; i++)
    {
        matrizProduto[i] = (double*) malloc(colunasB*sizeof(double));
        if(matrizProduto[i] == NULL) goto tratarErro;
    }

    for(i = 0; i < linhasA; i++)
        for(j = 0; j < colunasB; j++)
            matrizProduto[i][j] = 0;

    //Efetua a multiplicacao entre as matrizes
    for(i = 0; i < linhasA; i++)
    {
        for(j = 0; j < colunasB; j++)
        {
            for(k = 0; k < colunasA; k++)
                matrizProduto[i][j] += matrizA[i][k]*matrizB[k][j];
        }
    }

retorno:
    return matrizProduto;
tratarErro:
    if(matrizProduto != NULL)
    {
        for(i = 0; i < linhasA; i++)
        {
            if(matrizProduto[i] != NULL)
            {
                free(matrizProduto[i]);
                matrizProduto[i] = NULL;
            }
        }
        free(matrizProduto);
        matrizProduto = NULL;
    }
    goto retorno;
}

double** transposto(double **matriz, int linhas, int colunas)
{
    double** matrizTransposta = NULL;
    int i,j;

    matrizTransposta = (double**) malloc(colunas*sizeof(double*));
    if(matrizTransposta == NULL) goto tratarErro;
    for(i = 0; i < colunas; i++)
    {
        matrizTransposta[i] = (double*) malloc(linhas*sizeof(double));
        if(matrizTransposta[i] == NULL) goto tratarErro;
    }

    for(i = 0; i < colunas; i++)
        for(j = 0; j < linhas; j++)
            matrizTransposta[i][j] = matriz[j][i];

retorno:
    return matrizTransposta;
tratarErro:
    if(matrizTransposta != NULL)
    {
        for(i = 0; i < colunas; i++)
        {
            if(matrizTransposta[i] != NULL)
            {
                free(matrizTransposta[i]);
                matrizTransposta[i] = NULL;
            }
        }
        free(matrizTransposta);
        matrizTransposta = NULL;
    }
    goto retorno;
}
