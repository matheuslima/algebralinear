#include "matriz.h"

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

Matriz *criarMatrizAumentada(Matriz *matriz, Status *status)
{
    Matriz* matrizAumentada = NULL;
    int i, j;
    *status = sucesso;

    if(!MATRIZ_QUADRADA(matriz)){*status = erroMatrizNaoInvertivel; return NULL;}

    matrizAumentada = criarMatriz(matriz->linhas, 2*matriz->colunas);
    if(matrizAumentada == NULL) return NULL;

    // Copia a matriz passada como parametro para a metade esquerda da matriz aumentada
    for(i = 0; i < matriz->linhas; i++)
        for(j = 0; j < matriz->colunas; j++)
            matrizAumentada->conteudo[i][j] = matriz->conteudo[i][j];
    // Coloca uma matriz identidade na metdade direita da matriz aumentada
    for(i = 0; i < matriz->linhas; i++)
        matrizAumentada->conteudo[i][i+matriz->colunas] = 1;

    return matrizAumentada;
}

double* combinacaoLinear(double *X, double *Y, double a, double b, int tamanho)
{
    int i;
    double* vetor = NULL;
    vetor = (double*) malloc(tamanho*sizeof(double));
    if(vetor == NULL) goto tratarErro;

    for(i = 0; i < tamanho; i++)
    {
        vetor[i] = a*X[i] + b*Y[i];
    }
    return vetor;
    // Desaloca recurso caso haja problema na alocao de memoria
tratarErro:
    if(vetor != NULL)
    {
        free(vetor);
        vetor = NULL;
    }
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

    if(pMatrizProduto == NULL) return NULL;

    //Efetua a multiplicacao entre as matrizes
    for(i = 0; i < matrizA.linhas; i++)
    {
        for(j = 0; j < matrizB.colunas; j++)
        {
            for(k = 0; k < matrizA.colunas; k++)
                pMatrizProduto->conteudo[i][j] += matrizA.conteudo[i][k]*matrizB.conteudo[k][j];
        }
    }

    return pMatrizProduto;
}

Matriz *transposto(Matriz matriz)
{
    Matriz* matrizTransposta = NULL;
    int i,j;

    matrizTransposta = criarMatriz(matriz.colunas, matriz.linhas);
    if(matrizTransposta == NULL) return NULL;

    for(i = 0; i < matriz.linhas; i++)
        for(j = 0; j < matriz.colunas; j++)
            matrizTransposta->conteudo[j][i] = matriz.conteudo[i][j];

    return matrizTransposta;
}
