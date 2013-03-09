#include "gaussJordan.h"

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

Matriz *criarMatrizTriangular(Matriz *matrizAumentada, Status *status)
{
    Matriz* matrizTriangular = NULL;
    double pivo, elemento;
    double *linha = NULL;
    int i,j,k;
    *status = sucesso;

    // Aloca a matriz triangular e verifica a alocacao
    matrizTriangular = criarMatriz(matrizAumentada->linhas,matrizAumentada->colunas);
    if(matrizTriangular == NULL) return NULL;

    // Inicializa a matriz triangular com os elementos da matriz aumentada
    for(i = 0; i < matrizAumentada->linhas; i++)
        for(j = 0; j < matrizAumentada->colunas; j++)
            matrizTriangular->conteudo[i][j] = matrizAumentada->conteudo[i][j];

    // Zera os elementos abaixo do primeiro elemento da primeira coluna por
    // meio de combinacoes lineares entre as linhas
    for(i = 0; i < matrizTriangular->linhas - 1; i++)
    {
        pivo = matrizTriangular->conteudo[i][i];
        for(j = i+1; j < matrizTriangular->linhas; j++)
        {
            elemento = matrizTriangular->conteudo[j][i];
            // Se o primeiro elemento da coluna eh "a" e o elemento de uma linha
            // inferior na primeira coluna eh "b", entao para zerar o elemento
            // dessa linha, deve-se multiplicar a primeira linha por b/a e subtrair
            // o resultado da linha inferior. Essa combinacao linear deve substituir
            // a linha cujo elemento sera zerado
            linha = combinacaoLinear(matrizTriangular->conteudo[i],
                                     matrizTriangular->conteudo[j],
                                     -elemento/pivo,
                                     1,
                                     2*matrizTriangular->linhas);
            for(k = 0; k < matrizTriangular->colunas; k++)
                matrizTriangular->conteudo[j][k] = linha[k];
            free(linha);
            linha = NULL;
        }
    }
    return matrizTriangular;
}

bool verificarInvertibilidadeMatriz(Matriz* matrizTriangular)
{
    double determinante = 1;
    int i;
    for(i = 0; i < matrizTriangular->linhas; i++)
        determinante *= matrizTriangular->conteudo[i][i];
    return (determinante != 0);
}

Matriz *criarMatrizEscalonada(Matriz *matrizTriangular, Status *status)
{
    double pivo, elemento;
    double* linha = NULL;
    Matriz* matrizEscalonada = NULL;
    int i,j,k;
    *status = sucesso;
    matrizEscalonada = criarMatriz(matrizTriangular->linhas,matrizTriangular->colunas);
    if(matrizEscalonada == NULL) return NULL;


    // Inicializa a matriz escalonada com os elementos da matriz triangular
    for(i = 0; i < matrizTriangular->linhas; i++)
        for(j = 0; j < matrizTriangular->colunas; j++)
            matrizEscalonada->conteudo[i][j] = matrizTriangular->conteudo[i][j];

    // Zera os elementos acima dos pivos
    for(i = 1; i < matrizTriangular->linhas; i++)
        for(j = 0; j < i; j++)
        {
            pivo = matrizEscalonada->conteudo[i][i];
            elemento = matrizEscalonada->conteudo[j][i];
            linha = combinacaoLinear(matrizEscalonada->conteudo[i],
                                      matrizEscalonada->conteudo[j],
                                      -elemento/pivo,
                                      1,
                                      matrizEscalonada->colunas);
            for(k = 0; k < matrizEscalonada->colunas; k++)
                matrizEscalonada->conteudo[j][k] = linha[k];
            free(linha);
            linha = NULL;
        }

    // Divide cada linha pelo seu pivo
    for(i = 0; i < matrizTriangular->linhas; i++)
    {
        pivo = matrizEscalonada->conteudo[i][i];
        for(j = 0; j < matrizTriangular->colunas; j++)
        {
            matrizEscalonada->conteudo[i][j] = matrizEscalonada->conteudo[i][j]/pivo;
        }
    }
    return matrizEscalonada;
}

Matriz* criarMatrizInversa(Matriz *matriz)
{
    int i, j;
    Status status;
    Matriz *pMatrizAumentada = NULL, *pMatrizTriangular = NULL, *pMatrizEscalonada = NULL, *pMatrizInversa = NULL;

    pMatrizAumentada = criarMatrizAumentada(matriz, &status);
    // Se ocorreu algum erro na criacao da matriz aumentada, retorna NULL
    if(!OK(&status)) return NULL;

    pMatrizTriangular = criarMatrizTriangular(pMatrizAumentada, &status);
    // Se ocorreu algum erro na criacao da matriz triangular, retorna NULL
    if(!OK(&status)) return NULL;

    // Se a matriz nao for invertivel, retorna NULL
    if(!verificarInvertibilidadeMatriz(pMatrizTriangular)) return NULL;

    pMatrizEscalonada = criarMatrizEscalonada(pMatrizTriangular, &status);
    // Se ocorreu algum erro na criacao da matriz escalonada, retorna NULL
    if(!OK(&status)) return NULL;

    // Gera a matriz inversa
    pMatrizInversa = criarMatriz(matriz->linhas, matriz->linhas);
    for(i = 0; i < matriz->linhas; i++)
        for(j = 0; j < matriz->linhas; j++)
            pMatrizInversa->conteudo[i][j] = pMatrizEscalonada->conteudo[i][j+matriz->linhas];

    // Faz as desalocaoes
    destruirMatriz(pMatrizAumentada);
    destruirMatriz(pMatrizTriangular);
    destruirMatriz(pMatrizEscalonada);

    return pMatrizInversa;
}
