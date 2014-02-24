#include<stdio.h>
#include<string.h>
#include<time.h>
#include"gramSchmidt.h"
#include"matriz.h"
void imprimirMatriz(Matriz matriz);

#define MATRIX_FILE "matrix.dat"
#define MATRIX_DIMENSION 100
#define LENGTH_LINE MATRIX_DIMENSION*20

double **loadMatrix();

int main(void)
{
	int i, j;
	double **vetores = NULL;
	double **base = NULL;
	vetores = (double **) malloc(2*sizeof(double *));
	vetores[0] = (double *) malloc(3*sizeof(double));
	vetores[1] = (double *) malloc(3*sizeof(double));
	vetores[0][0] = 1; vetores[0][1] = 2; vetores[0][2] = 3;
	vetores[1][0] = 1; vetores[1][1] = -2; vetores[1][2] = 3;
	base = (double **) obterBaseOrtonormal(vetores, 2, 3);
	printf("Base de [1 2 3] e [1 -2 3]:\n");
	for(i = 0; i < 2; i++)
	{
		printf("[ ");
		for(j = 0; j < 3; j++)
			printf("%f ", base[i][j]);
		printf("]\n");
	}
	for(i = 0; i < 2; i++)
	{
		free(vetores[i]);
		free(base[i]);
	}
	free(vetores);
	free(base);
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
    	matrix = (double **)malloc(MATRIX_DIMENSION*sizeof(double*));
    	if (matrix == NULL) return NULL;
    	for(i = 0; i < MATRIX_DIMENSION; i++){
        	matrix[i] = (double*)malloc(MATRIX_DIMENSION*sizeof(double));
        	if(matrix[i] == NULL) return NULL;
    	}

	FILE *pFile = NULL;
    	pFile = fopen(MATRIX_FILE, "r");

    	for(i = 0; i < MATRIX_DIMENSION; i++)
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
        	while(j < MATRIX_DIMENSION-1){
            		j++;
            		buffer = strtok(NULL, " ");
            		matrix[i][j] = atof(buffer);
       		}
    	}
    	fclose(pFile);
    	return matrix;
}
