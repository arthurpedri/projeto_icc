#include "lib.h"

void testa_parametros(int argc, char const *argv[]){

    n = atoi(argv[1]);
    maxIter = n;
    if (n < 0) {
        fprintf(stderr, "ERRO: n negativo: %s\n", argv[1]);
        exit(-1);
    }
    nBandas = atoi(argv[2]);
    if (nBandas < 0) {
        fprintf(stderr, "ERRO: nBandas negativo: %s\n", argv[2]);
        exit(-1);
    }
    else if (nBandas % 2 == 0){
        fprintf(stderr, "ERRO: nBandas par: %s\n", argv[2]);
        exit(-1);
    }
    int i = 3;
    if (!strcmp(argv[i],"-i")) {
        i++;
        maxIter = atoi(argv[i]);
        i++;
    }
    if (!strcmp(argv[i],"-t")) {
        i++;
        tolerancia = atof(argv[i]);
        i++;
    }
    if (!strcmp(argv[i],"-o")) {
        i++;
        arquivo_saida = malloc(sizeof(char) * strlen(argv[i]));
        strcpy(arquivo_saida, argv[i]);
        output = fopen(arquivo_saida, "wr");
    } else {
        fprintf(stderr, "ERRO: parametro \"%s\" não reconhecido\n", argv[i]);
        exit(-1);
    }
}

double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

/***********************
 * N: tamanho do sistema linear
 * k: numero da diagonal, 0 = diagonal principal, 1 = acima/abaixo da diagonal, 2 = ...
 * nBandas: numero de bandas do sistema linear
 * diag: vetor para armazenar os valores da diagonal. Deve ser alocado por quem chama a função.
 ***********************/
int generateRandomDiagonal( unsigned int N, unsigned int k, unsigned int nBandas, double *diag )
{
  if ( !diag || N < 3 || nBandas > N/2 || k < 0 || k > nBandas )
    return (-1);

  /* garante valor dominante para diagonal principal */
  double fator = (k == 0) ? ((double)(nBandas-1)) : (0.0);

  double invRandMax = 1.0 / (double)RAND_MAX;

  for (int i=0; i < N-k; ++i)
  {
    diag[i] = fator + (double)rand() * invRandMax;
  }

  return (0);
}

void imprimeMatriz (double *matriz){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%.5g ", matriz[i*n +j]);
        }
        printf("\n");
    }
}

void imprimeVetor (double *vetor, int max){
    for (int i = 0; i < max; i++){
        printf("%.14g ", vetor[i]);
    }
    printf("\n");
}

double produtoInterno (double *vetor1, double *vetor2){
    double resultado = 0.0;
    for (int i = 0; i < n; i++){
       resultado = resultado + (vetor1[i] * vetor2[i]);
    }
    return resultado;
}

void subtracaoVetores (double *resultado, double *vetor1, double *vetor2){
    for (int i = 0; i < n; i++){
        resultado[i] = vetor1[i] - vetor2[i];
    }
}

double norma_residuo(double *r){
    double resultado;
    for(int i = 0; i < n; i++){
        resultado += r[i] * r[i];
    }
    return sqrt(resultado);
}

void produtoMatrizVetor (double *resultado, double *matriz, double *vetor){ // melhorar para não multiplicar os zeros
    double soma;
    int k = nBandas/2;
    for(int i = 0; i < n; i++){
        soma = 0.0;
        for(int j = 0; j < n; j++){
            if((i - j) < k){
                soma = soma + (matriz[i*n + j] * vetor[j]);
            }
        }
        resultado[i] = soma;
    }
}



double f (double x){
    return 4*(M_PI*M_PI)*(sin((2*M_PI)*x) + sin(2*M_PI*(M_PI-x)));
}



void imprimeArquivo(double *tempoIter, double *tempoRes, double *res, double *erroAprox, double *X, int k){

        // int i, j;
        double menorRes = tempoRes[0], maiorRes = tempoRes[0], menorIter = tempoIter[0], maiorIter = tempoIter[0];
        double mediaIter = tempoIter[0], mediaRes = tempoRes[0];
        for (int i = 1; i < k; i++){
            if (tempoRes[i] < menorRes){
                menorRes = tempoRes[i];
            } else if (tempoRes[i] > maiorRes){
                maiorRes = tempoRes[i];
            }
            if (tempoIter[i] < menorIter){
                menorIter = tempoIter[i];
            } else if (tempoIter[i] > maiorIter){
                maiorIter = tempoIter[i];
            }
            mediaIter += tempoIter[i];
            mediaRes += tempoRes[i];
        }
        mediaIter = mediaIter/k;
        mediaRes = mediaRes/k;

        fprintf(output,"###########\n");
        fprintf(output, "# Tempo Método CG: %lf %lf %lf\n", fabs(menorIter), fabs(mediaIter), fabs(maiorIter));
        fprintf(output, "# Tempo Resíduo: %lf %lf %lf\n", fabs(menorRes), fabs(mediaRes), fabs(maiorRes));
        fprintf(output, "#\n# Norma Euclidiana do Residuo e Erro aproximado\n");

        for (int i = 0; i < k; i++) {
            fprintf(output, "# i=%d: %.14g %.14g\n", i, res[i], erroAprox[i]);
        }
        fprintf(output, "###########\n");
        fprintf(output, "%d\n", n);
        for (int i = 0; i < n; i++){
            fprintf(output, "%.14g ", X[i]);
        }
}
