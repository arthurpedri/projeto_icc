#include "lib.h"
int main(int argc, char const *argv[]) {
    srand( 20162 );
    tolerancia = LDBL_EPSILON;
    testa_parametros(argc, argv);

    //matriz A
    // double **A = (double **) calloc(n, sizeof(double));
    // for (int i = 0; i < n; i++){
    //     A[i] = (double *) calloc(n, sizeof(double));
    // }
    double *A = (double *) malloc(sizeof(double)*n*n);

    if (A == NULL){
        fprintf(stderr, "Erro durante alocacao de memoria para matriz A\n");
        exit(-1);
    }
    //vetor para armazenar a diagonal gerada
    double *diag = (double *) malloc(sizeof(double)*n);
    if (diag == NULL){
        fprintf(stderr, "Erro durante alocacao de memoria para vetor da diagonal\n");
        exit(-1);
    }

    /*
    * X : Vetor solucao X, inicializado com 0 pela calloc();
    * r : Vetor para o residuo r em cada iteracao
    * b : Vetor de termos independentes b;
    */
    double *X = (double *) calloc(n, sizeof(double)); //Vetor solucao, inicializado com 0
    double *r = (double *) malloc(sizeof(double)*n); //Vetor residuo
    double *b = (double *) malloc(sizeof(double)*n); //Vetor b

    //Cria valores do vetor b
    //M_PI_n = M_PI / n
    //b[i] = f(i * M_PI_n)
    for (int i = 0; i < n; i++){
        b[i] = f((i*M_PI)/n);
    }

    imprimeVetor(b, n);
    //Cria matriz A com as diagonais
    for (int k = 0; k <= nBandas/2; k++){
        generateRandomDiagonal(n, k, nBandas, diag );
        for (int i = 0; i < n - k; i++){ // percorre o vetor
            // A[i][i + k] = diag[i];
            // A[i + k][i] = diag[i];
            A[i*n + (i + k)] = diag[i];
            A[(i + k)*n + i] = diag[i];
        }
    }
    /*
    * AX - Vetor auxiliar para armazenar A * X;
    * Ar = Vetor auxiliar para armazenar A * r;
    * v_res = Vetor para guardar a norma de cada iteracao;
    * v_erroAprox = Vetor para guardar o erro absoluto aproximado de cada iteracao;
    * v_tempoRes = Vetor para armazenar o tempo gasto no calculo de cada residuo;
    * v_tempoIter = Vetor para armazenar o tempo gasto na execucao de cada iteracao;
    * norma_res_old = Guarda o valor da norma da iteracao anterior
    * s = variavel auxiliar, s = r'r / r'Ar
    */
    double *AX = (double *) malloc(sizeof(double)*n);
    double *Ar = (double *) malloc(sizeof(double)*n);
    double *v_res = (double *) malloc(sizeof(double)* maxIter);
    double *v_erroAprox = (double *) malloc(sizeof(double)* maxIter);
    double *v_tempoRes = (double *) malloc(sizeof(double)* maxIter);
    double *v_tempoIter = (double *) malloc(sizeof(double)* maxIter);
    double norma_res_old = 0.0;
    double s;
    int k = 0;

    for(k = 0; k < maxIter; k++){
        t_iter_a = timestamp();
        produtoMatrizVetor(AX, A, X);
        t_residuo_a = timestamp();
        for (int i = 0; i < n; i++) {
            r[i] = b[i] - AX[i];
        }
        v_res[k] = norma_residuo(r);
        t_residuo_b = timestamp();

        produtoMatrizVetor(Ar, A, r);
        s = produtoInterno(r, r) / produtoInterno(r, Ar);
        for (int i = 0; i < n; i++) {
            X[i] = X[i] + s * r[i];
        }

        t_iter_b = timestamp();
        v_tempoIter[k] = t_iter_b - t_iter_a;

        v_tempoRes[k] = t_residuo_b - t_residuo_a;

        v_erroAprox[k] = fabs(v_res[k] - norma_res_old);
        norma_res_old = v_res[k];



        if (v_erroAprox[k] <= tolerancia){
            break;
        }
    }

    imprimeArquivo(v_tempoIter, v_tempoRes, v_res, v_erroAprox, AX, k);

    //Desaloca as estruturas
    free(A);
    free(X);
    free(r);
    free(b);
    free(AX);
    free(Ar);
    free(v_erroAprox);
    free(v_res);
    free(v_tempoIter);
    free(v_tempoRes);

    fclose(output);
    //for (int i = 0; i < n; i++){
    //    printf("b - Ax = : %.14g, b[i] : %.14g , AX[i]: %.14g, Tolerancia: %.14g, Iter: %d\n", b[i] - AX[i], b[i], AX[i], tolerancia, k);
    //}
}
