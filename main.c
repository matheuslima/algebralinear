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
	double vetor[] = {1, 2, 3};
	double *vetorUnit = obterVetorUnitario(vetor, 3);
	double vetA[] = {1, 2, 3};
	double vetB[] = {1, -2, 3};
	double *proj = NULL;
	double **base = NULL;
	double **vetores = NULL;
	int i, j;
	printf("Vetor unitario: [%f, %f, %f]\n", vetorUnit[0], vetorUnit[1], vetorUnit[2]);
	proj = obterProjecao(vetA, vetB, 2);
	printf("Projecao de [1 2 3] sobre [1 -2 3]: [%f %f]\n", proj[0], proj[1]);
	printf("Base ortonormal de [1 2 3] e [1 -2 3]:\n");
	vetores = (double **) malloc(2*sizeof(double *));
	if(vetores == NULL) return -1;
	vetores[0] = vetA;
	vetores[1] = vetB;
	base = obterBaseOrtonormal(vetores, 2, 3);
	for(i = 0; i < 2; i++)
	{
		printf("[ ");
		for(j = 0; j < 3; j++)
			printf("%f ", base[i][j]);
		printf("]\n");

	}
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
