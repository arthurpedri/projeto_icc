#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

/* VARIAVEIS */
int n, nBandas, maxIter;
char *arquivo_saida;
double tolerancia;
FILE *output;

/* PROTOTIPOS DAS FUNCOES */
void testa_parametros(int argc, char const *argv[]);
double timestamp();
int generateRandomDiagonal( unsigned int N, unsigned int k, unsigned int nBandas, double *diag );
void imprimeMatriz (double **matriz, int N);
// void grava_arquivo(double *matriz, double *res, int n, int nx, int ny, double hx, double hy, double sor_time, double res_time);