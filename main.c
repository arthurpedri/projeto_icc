#include "lib.h"
#define E 0.00001
int main(int argc, char const *argv[]) {
    srand( 20162 );
    testa_parametros(argc, argv);
  
    fprintf(output, "Bandas: %d, maxIter: %d, tolerancia: %.5g", nBandas, maxIter, tolerancia);
    
    //matriz A
    double **A = (double **) calloc(n * n, sizeof(double));
    if (A == NULL){
        printf("Erro malloc A\n");
        fprintf(stderr, "Erro durante alocacao de memoria para matriz A\n");
        exit(-1);
    }
    //vetor para armazenar a diagonal gerada
    double *diag = (double *) malloc(sizeof(double)*n);
    if (diag == NULL){
        printf("Erro malloc diag\n");
        fprintf(stderr, "Erro durante alocacao de memoria para vetor da diagonal\n");
        exit(-1);
    }
    //Vetor solucao
    double *X = (double *) calloc(n, sizeof(double));
    
    for (int k = 0; k <= nBandas; k++){
        // generateRandomDiagonal(n, k, nBandas, diag );
        for (int i = 0; i < n - k; i++){ // percorre o vetor
            // diag[i] = i * 2 + k;
            A[i][i + k] = diag[i];
            A[i + k][i] = diag[i];
            fprintf(output, "%.5g ", diag[i]);
        }
    }
    
    imprimeMatriz(A, n);
} 



