#include"gramSchmidt.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double *obterVetorUnitario(double *vetor, int tamanho)
{
	int i;
	double modulo = 0;
	double *vetorUnit = NULL;
	vetorUnit = (double *) malloc(tamanho*sizeof(double));
	if(vetorUnit == NULL) return NULL;

	for(i = 0; i < tamanho; i++)
		modulo += vetor[i]*vetor[i];
	modulo = sqrt(modulo);
	for(i = 0; i < tamanho; i++)
		vetorUnit[i] = vetor[i]/modulo;
	return vetorUnit;
}

double *subtrairVetores(double *vetorA, double *vetorB, int tamanho)
{
	int i;
	double *vetor = NULL;
	vetor = (double *) malloc(tamanho*sizeof(double));
	if(vetor == NULL) return NULL;
	
	for(i = 0; i < tamanho; i++)
		vetor[i] = vetorA[i] - vetorB[i];
	return vetor;
}

double *obterProjecao(double *vetorA, double *vetorB, int tamanho)
{
	int i = 0;
	double produto = 0;
	double moduleB = 0;
	double *vetorResult;
	double *vetorUnit = NULL;
	vetorUnit = obterVetorUnitario(vetorB, tamanho);
	vetorResult = (double *) malloc(tamanho*sizeof(double));
	for(i = 0; i < tamanho; i++)
		produto += vetorA[i]*vetorUnit[i];
	for(i = 0; i < tamanho;i ++)
		vetorResult[i] = produto*vetorUnit[i];
	free(vetorUnit);
	return vetorResult;

}

double **obterBaseOrtonormal(double **vetores, int quantidade, int tamanho)
{
	int i, j;
	double **base = NULL;
	base = (double **) malloc(quantidade*sizeof(double *));
	double *projecao = NULL;
	double *buffer = NULL;
	if(base == NULL) return NULL;

	for(i = 0; i < quantidade; i++)
		base[i] = NULL;

	for(i = 0; i < quantidade; i++)
	{
		base[i] = vetores[i];
		for(j = 0; j < i; j++)
		{
			projecao = obterProjecao(vetores[i], vetores[j], tamanho);
			buffer =   subtrairVetores(base[i], projecao, tamanho);
			memcpy(base[i],buffer, tamanho*sizeof(double));
			free(projecao);
			free(buffer);
		}
		buffer =  obterVetorUnitario(base[i], tamanho);
		memcpy(base[i], buffer, tamanho*sizeof(double));
		free(buffer);
	}

	return base;
}
