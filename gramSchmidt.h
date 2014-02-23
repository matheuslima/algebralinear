#ifndef GRAMSCHMIDT
#define GRAMSCHMIDT

double *obterVetorUnitario(double *vetor, int tamanho);

double *subtrairVetores(double *vetorA, double *vetorB);

// Projeta o vetor A sobre o vetor B
double *obterProjecao(double *vetorA, *double vetorB, int tamanho);

// Obtem um espaco ortonormal a partir do algoritmo de ortogonalizacao de Gram-Schmidt
double **obterEspacoOrtonormal(double **vetores, int quantidade, int tamanho);
#endif
