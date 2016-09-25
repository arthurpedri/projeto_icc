#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Constantes e variáveis */
#define M_PI 3.14159265358979323846
int n, nBandas, maxIter;
char *arquivo_saida;
double tolerancia, t_residuo_a, t_residuo_b;
FILE *output;


/* PROTOTIPOS DAS FUNCOES */
void testa_parametros(int argc, char const *argv[]);
double timestamp();
int generateRandomDiagonal( unsigned int N, unsigned int k, unsigned int nBandas, double *diag );
void imprimeMatriz (double **matriz);
void imprimeVetor (double *vetor, int max);
double produtoInterno (double *vetor1, double *vetor2);
void subtracaoVetores (double *resultado, double *vetor1, double *vetor2);
double norma_residuo(double *r);
void produtoMatrizVetor (double *resultado, double **matriz, double *vetor);
double f (double x);
// void grava_arquivo(double *matriz, double *res, int n, int nx, int ny, double hx, double hy, double sor_time, double res_time);