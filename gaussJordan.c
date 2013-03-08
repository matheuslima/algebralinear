#include "gaussJordan.h"

double** criarMatrizAumentada(int dimensao, double** matriz, Status *status)
{
    double** matrizAumentada = NULL;
    int i, j;
    *status = sucesso;
    matrizAumentada = (double**) malloc(dimensao*sizeof(double*));
    if(matrizAumentada == NULL) {*status = erroAlocacao; goto tratarErro;}
    for(i = 0; i < dimensao; i++)
    {
        matrizAumentada[i] = (double*) malloc(2*dimensao*sizeof(double));
        if(matrizAumentada[i]==NULL){ *status = erroAlocacao; goto tratarErro;}
    }
    // Inicializa a matriz aumentada com zeros
    for(i = 0; i < dimensao; i++)
        for(j = 0; j < 2*dimensao; j++)
            matrizAumentada[i][j] = 0;
    // Copia a matriz passada como parametro para a metade esquerda da matriz aumentada
    for(i = 0; i < dimensao; i++)
        for(j = 0; j < dimensao; j++)
            matrizAumentada[i][j] = matriz[i][j];
    // Coloca uma matriz identidade na metdade direita da matriz aumentada
    for(i = 0; i < dimensao; i++)
        matrizAumentada[i][i+dimensao] = 1;

retorno:
    return matrizAumentada;

tratarErro:
    if(matrizAumentada != NULL)
    {
        for(i = 0; i < dimensao; i++)
        {
            if(matrizAumentada[i] != NULL)
            {
                free(matrizAumentada[i]);
                matrizAumentada[i] = NULL;
            }
        }
        free(matrizAumentada);
        matrizAumentada = NULL;
    }
    goto retorno;
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
retorno:
    return vetor;
    // Desaloca recurso caso haja problema na alocao de memoria
tratarErro:
    if(vetor != NULL)
    {
        free(vetor);
        vetor = NULL;
    }
    goto retorno;
}

double** criarMatrizTriangular(int dimensao, double **matrizAumentada, Status *status)
{
    double** matrizTriangular = NULL;
    double pivo, elemento;
    int i,j;
    *status = sucesso;

    // Aloca a matriz triangular e verifica a alocacao
    matrizTriangular = (double**) malloc(dimensao*sizeof(double*));
    if(matrizTriangular == NULL) { *status = erroAlocacao; goto tratarErro;}
    for(i = 0; i < dimensao; i++)
    {
        matrizTriangular[i] = (double*) malloc(2*dimensao*sizeof(double));
        if(matrizTriangular[i] == NULL) {*status = erroAlocacao; goto tratarErro;}
    }

    // Inicializa a matriz triangular com os elementos da matriz aumentada
    for(i = 0; i < dimensao; i++)
        for(j = 0; j < 2*dimensao; j++)
            matrizTriangular[i][j] = matrizAumentada[i][j];

    // Zera os elementos abaixo do primeiro elemento da primeira coluna por
    // meio de combinacoes lineares entre as linhas
    for(i = 0; i < dimensao - 1; i++)
    {
        pivo = matrizTriangular[i][i];
        for(j = i+1; j < dimensao; j++)
        {
            elemento = matrizTriangular[j][i];
            // Se o primeiro elemento da coluna eh "a" e o elemento de uma linha
            // inferior na primeira coluna eh "b", entao para zerar o elemento
            // dessa linha, deve-se multiplicar a primeira linha por b/a e subtrair
            // o resultado da linha inferior. Essa combinacao linear deve substituir
            // a linha cujo elemento sera zerado
            matrizTriangular[j] = combinacaoLinear(matrizTriangular[i],
                                                   matrizTriangular[j],
                                                   -elemento/pivo,
                                                   1,
                                                   2*dimensao);
        }
    }
retorno:
    return matrizTriangular;

    // Caso haja algum problema nas alocacoes de memoria, faz a liberacao
    // dos recursos alocados
tratarErro:
    if(matrizTriangular != NULL)
    {
        for(i = 0; i < dimensao; i++)
        {
            if(matrizTriangular[i] != NULL)
            {
                free(matrizTriangular[i]);
                matrizTriangular[i] = NULL;
            }
        }
        free(matrizTriangular);
        matrizTriangular = NULL;
    }
    goto retorno;
}

bool verificarInvertibilidadeMatriz(int dimensao, double **matrizTriangular)
{
    double determinante = 1;
    int i;
    for(i = 0; i < dimensao; i++)
        determinante *= matrizTriangular[i][i];
    return (determinante != 0);
}

double** criarMatrizEscalonada(int dimensao, double **matrizTriangular, Status *status)
{
    double pivo, elemento;
    double** matrizEscalonada = NULL;
    int i,j;
    *status = sucesso;
    matrizEscalonada = (double**) malloc(dimensao*sizeof(double*));
    if(matrizEscalonada == NULL){*status = erroAlocacao; goto tratarErro;}
    for(i = 0; i < dimensao; i++)
    {
        matrizEscalonada[i] = (double*) malloc(2*dimensao*sizeof(double));
        if(matrizEscalonada[i] == NULL){*status = erroAlocacao; goto tratarErro;}
    }

    // Inicializa a matriz escalonada com os elementos da matriz triangular
    for(i = 0; i < dimensao; i++)
        for(j = 0; j < 2*dimensao; j++)
            matrizEscalonada[i][j] = matrizTriangular[i][j];

    // Zera os elementos acima dos pivos
    for(i = 1; i < dimensao; i++)
        for(j = 0; j < i; j++)
        {
            pivo = matrizEscalonada[i][i];
            elemento = matrizEscalonada[j][i];
            matrizEscalonada[j] = combinacaoLinear(matrizEscalonada[i],
                                                   matrizEscalonada[j],
                                                   -elemento/pivo,
                                                   1,
                                                   2*dimensao);
        }

    // Divide cada linha pelo seu pivo
    for(i = 0; i < dimensao; i++)
    {
        pivo = matrizEscalonada[i][i];
        for(j = 0; j < 2*dimensao; j++)
        {
            matrizEscalonada[i][j] = matrizEscalonada[i][j]/pivo;
        }
    }
retorno:
    return matrizEscalonada;
    // Desaloca os recurso previamente alocados em caso de algum erro
tratarErro:
    if(matrizEscalonada != NULL)
    {
        for(i = 0; i < dimensao; i++)
        {
            if(matrizEscalonada[i] != NULL)
            {
                free(matrizEscalonada[i]);
                matrizEscalonada[i] = NULL;
            }
        }
        free(matrizEscalonada);
        matrizEscalonada = NULL;
    }
    goto retorno;
}

double** criarMatrizInversa(int dimensao, double **matriz)
{
    int i, j;
    Status status;
    double **pMatrizAumentada, **pMatrizTriangular, **pMatrizEscalonada, **pMatrizInversa;

    pMatrizAumentada = criarMatrizAumentada(dimensao, matriz, &status);
    // Se ocorreu algum erro na criacao da matriz aumentada, retorna NULL
    if(!OK(&status)) return NULL;

    pMatrizTriangular = criarMatrizTriangular(dimensao, pMatrizAumentada, &status);
    // Se ocorreu algum erro na criacao da matriz triangular, retorna NULL
    if(!OK(&status)) return NULL;

    // Se a matriz nao for invertivel, retorna NULL
    if(!verificarInvertibilidadeMatriz(dimensao, pMatrizTriangular)) return NULL;

    pMatrizEscalonada = criarMatrizEscalonada(dimensao, pMatrizTriangular, &status);
    // Se ocorreu algum erro na criacao da matriz escalonada, retorna NULL
    if(!OK(&status)) return NULL;

    pMatrizInversa = (double**) malloc(dimensao*sizeof(double*));
    if(pMatrizInversa == NULL) goto tratarErro;
    for(i = 0; i < dimensao; i++)
    {
        pMatrizInversa[i] = (double*) malloc(2*dimensao*sizeof(double));
        if(pMatrizInversa == NULL) goto tratarErro;
    }
    for(i = 0; i < dimensao; i++)
        for(j = 0; j < dimensao; j++)
            pMatrizInversa[i][j] = pMatrizEscalonada[i][j+dimensao];


retorno:
    return pMatrizInversa;
tratarErro:
    if(pMatrizInversa != NULL)
    {
        for(i = 0; i < dimensao; i++)
        {
            if(pMatrizInversa[i] != NULL)
            {
                free(pMatrizInversa[i]);
                pMatrizInversa[i] = NULL;
            }
            free(pMatrizInversa);
            pMatrizInversa = NULL;
        }

    }
    goto retorno;
}
