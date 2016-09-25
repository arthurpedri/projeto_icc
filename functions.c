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

void imprimeMatriz (double **matriz){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%.5g ", matriz[i][j]);
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
        resultado += pow(r[i], 2);
    }
    return sqrt(resultado);
}

void produtoMatrizVetor (double *resultado, double **matriz, double *vetor){ // melhorar para não multiplicar os zeros
    for(int i = 0; i < n; i++){
        resultado[i] = produtoInterno(matriz[i],vetor);
    }
}



double f (double x){
    return 4*(M_PI*M_PI)*(sin((2*M_PI)*x) + sin(2*M_PI*(M_PI-x)));
}

// void grava_arquivo(){
        // int i, j;
        // fprintf(output,"#########################################\n");
        // fprintf(output, "# Tempo Método CG: %lf\n", sor_time);
        // fprintf(output, "# Tempo Resíduo: %lf\n", res_time);
        // fprintf(output, "#\n# Norma Euclidiana do Residuo e Erro aproximado");

        // for (i = 0; i < maxIter; i++) {
        //     fprintf(output, "# i=%d: %f\n", i, res[i]);
        // }
        // fprintf(output, "#########################################\n");
        // fprintf(output, "%d\n", n);

        // //GNU plot
        // fprintf(output, "set title  'ICC'\n");
        // fprintf(output, "set xlabel 'x'\n");
        // fprintf(output, "set ylabel 'y'\n");
        // fprintf(output, "set zlabel 'z'\n");
//      fprintf(output, "splot '-' with lines\n");

        //Vetor solucao
//      for (i = 0; i < ny; i++) {
//         for (j = 0; j < nx; j++) {
//             fprintf(output,"%.3f %.3f %.3f\n", (hx*j), (hy *i), matriz[i*nx+j]);
//         }
//     }
// }
