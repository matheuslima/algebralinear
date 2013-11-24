#include<stdio.h>
#include<string.h>
#include<time.h>
#include"gaussJordan.h"
#include"matriz.h"
void imprimirMatriz(Matriz matriz);

#define MATRIX_FILE "matrix.dat"
#define LENGTH_LINE 100*20

double **loadMatrix();

int main(void)
{
    double **matrix = loadMatrix();
    int i, j;
    struct timespec start, stop;
    if(matrix == NULL) exit(1);
    Matriz *pMatriz = NULL;
    pMatriz = criarMatriz(100, 100);
    for(i = 0; i < 100; i++)
        for(j = 0; j < 100; j++)
            pMatriz->conteudo[i][j] = matrix[i][j];
    clock_gettime(CLOCK_MONOTONIC, &start);
    double det = determinant(pMatriz);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    printf("Determinante: %f\n", det);
    printf("Tempo de calculo: %ld ns\n", ((stop.tv_sec * 1000000000) + stop.tv_nsec) -
           ((start.tv_sec * 1000000000) + start.tv_nsec));
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

double **loadMatrix(){
    char line[LENGTH_LINE];
    char c;
    char *buffer = NULL;
    int i, j;
    if(line == NULL) return NULL;
    double **matrix = NULL;
    matrix = (double **)malloc(100*sizeof(double*));
    if (matrix == NULL) return NULL;
    for(i = 0; i < 100; i++){
        matrix[i] = (double*)malloc(100*sizeof(double));
        if(matrix[i] == NULL) return NULL;
    }

    FILE *pFile = NULL;
    pFile = fopen(MATRIX_FILE, "r");

    for(i = 0; i < 100; i++)
    {
        memset(line, '\0', LENGTH_LINE);
        j = 0;
        do{
            c = getc(pFile);
            line[j++] = c;
        }while(c != '\n' && c != EOF);
        j = 0;
        buffer = strtok(line, " ");
        matrix[i][j] = atof(buffer);
        while(j < 99){
            j++;
            buffer = strtok(NULL, " ");
            matrix[i][j] = atof(buffer);
        }
    }
    fclose(pFile);
    return matrix;
}
