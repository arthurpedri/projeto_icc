#include "lib.h"

void testa_parametros(int argc, char const *argv[]){
    
    n = atoi(argv[1]);
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

void imprimeMatriz (double **matriz, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%.5g ", matriz[i][j]);
        }
        printf("\n");
    }
}

// void grava_arquivo(double *matriz, double *res, int n, int nx, int ny, double hx, double hy, double sor_time, double res_time){
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
