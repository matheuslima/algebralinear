#include "matrizes.h"

Matriz* criarMatriz(int linhas, int colunas)
{
    int i,j;
    Matriz* matriz = NULL;
    matriz = (Matriz*) malloc(sizeof(Matriz));

    if(matriz == NULL) return NULL;

    matriz->conteudo = (double**) malloc(linhas*sizeof(double*));
    if(matriz->conteudo == NULL) goto tratarErro;

    for(i = 0; i < linhas; i++)
    {
        matriz->conteudo[i] = (double*) malloc(colunas*sizeof(double));
        if(matriz->conteudo[i] == NULL) goto tratarErro;
    }

    // Inicializa a matriz
    for(i = 0; i < linhas; i++)
        for(j = 0; j < colunas; j++)
            matriz->conteudo[i][j] = 0;

    matriz->linhas = linhas;
    matriz->colunas = colunas;

    return matriz;
tratarErro:
    destruirMatriz(matriz);
    return NULL;
}

void destruirMatriz(Matriz *matriz)
{
    int i;
    if(matriz != NULL)
    {
        if(matriz->conteudo != NULL)
        {
            for(i = 0; i < matriz->linhas; i++)
            {
                if(matriz->conteudo[i] != NULL)
                {
                    free(matriz->conteudo[i]);
                    matriz->conteudo[i] = NULL;
                }
            }
            free(matriz->conteudo);
            matriz->conteudo = NULL;
        }
        free(matriz);
        matriz = NULL;
    }
}

Matriz* produto(Matriz matrizA, Matriz matrizB)
{
    Matriz* pMatrizProduto = NULL;
    int i,j,k;
    // Verifica se o produto pode ser feito. Isso ocorre se colunasA == linhasB
    bool produtoPossivel = matrizA.colunas == matrizB.linhas;
    if(!produtoPossivel) return NULL;

    pMatrizProduto = criarMatriz(matrizA.linhas, matrizB.colunas);

    if(pMatrizProduto == NULL) goto tratarErro;

    //Efetua a multiplicacao entre as matrizes
    for(i = 0; i < matrizA.linhas; i++)
    {
        for(j = 0; j < matrizB.colunas; j++)
        {
            for(k = 0; k < matrizA.colunas; k++)
                pMatrizProduto->conteudo[i][j] += matrizA.conteudo[i][k]*matrizB.conteudo[k][j];
        }
    }

retorno:
    return pMatrizProduto;
tratarErro:
    destruirMatriz(pMatrizProduto);
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
