#include "lib.h"
#define E 0.00001
int main(int argc, char const *argv[]) {
    srand( 20162 );
    tolerancia = E;
    testa_parametros(argc, argv);
    
  
    //fprintf(output, "Bandas: %d, maxIter: %d, tolerancia: %.5g", nBandas, maxIter, tolerancia);
    
    //matriz A
    double **A = (double **) calloc(n, sizeof(double));
    for (int i = 0; i < n; i++){
        A[i] = (double *) calloc(n, sizeof(double));
    }
    
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
    
    double *X = (double *) calloc(n, sizeof(double)); //Vetor solucao, inicializado com 0
    double *r = (double *) malloc(sizeof(double)*n); //Vetor residuo
    double *b = (double *) malloc(sizeof(double)*n); //Vetor b
    
    //Cria valores do vetor b
    for (int i = 0; i < n; i++){
        b[i] = f((i*M_PI)/n);
    }
    
    //Cria matriz A com as diagonais
    for (int k = 0; k <= nBandas; k++){
        generateRandomDiagonal(n, k, nBandas, diag );
        for (int i = 0; i < n - k; i++){ // percorre o vetor
            A[i][i + k] = diag[i];
            A[i + k][i] = diag[i];
            //fprintf(output, "%.5g ", diag[i]);
        }
    }
    
    
    double *AX = (double *) malloc(sizeof(double)*n); // valor calculado para b;
    double *Ar = (double *) malloc(sizeof(double)*n);
    double *v_res = (double *) malloc(sizeof(double)* maxIter);
    double *v_erroAprox = (double *) malloc(sizeof(double)* maxIter);
    double *v_tempoRes = (double *) malloc(sizeof(double)* maxIter);
    double norma_res_old = 0.0;
    double s;
    imprimeMatriz(A);
    
    for(int k = 0; k < maxIter; k++){
        printf("iteracao %d\n", k);
        produtoMatrizVetor(AX, A, X);
        for (int i = 0; i < n; i++) {
            r[i] = b[i] - AX[i]; 
            printf("r[%d]: %.14g b[%d]: %.14g\n", i, r[i], i, b[i]);
            printf("Ax[%d]: %.14g\n", i, AX[i]);
        }
        //imprimeVetor(AX, n);
        //imprimeVetor(b);
        produtoMatrizVetor(Ar, A, r);
        s = produtoInterno(r, r) / produtoInterno(r, Ar);
        for (int i = 0; i < n; i++) {
            X[i] = X[i] + s * r[i];
        }

        t_residuo_a = timestamp();
        v_res[k] = norma_residuo(r);
        t_residuo_b = timestamp();
        
        v_tempoRes[k] = t_residuo_a - t_residuo_b;
        
        v_erroAprox[k] = fabs(v_res[k] - norma_res_old);
        printf("erro[%d] : %.14g\n", k, v_erroAprox[k]);
        norma_res_old = v_res[k];

        if (v_erroAprox[k] <= tolerancia)
            break;
    }
    //imprimeVetor(v_res, maxIter);
    //imprimeVetor(v_erroAprox, maxIter);
} 



