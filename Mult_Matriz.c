#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <unistd.h>    // sync()
#include <stdint.h> /* for uint64 definition */

#define BILLION 1000000000L

void PrintMatriz(double **M, int l, int c){
  int i, j;
  for(i = 0; i < l; i++){
    for(j = 0; j < c; j++){
      printf("%.1lf ", M[i][j] );
    }
    printf("\n");
  }
  printf("\n");

}
// Gera Matriz
void geraMatriz(double **M, int l, int c){
  int i, j;
  for(i = 0; i < l; i++){
    for(j = 0; j < c; j++){
      M[i][j] = (double)(rand() % 1000 + 1)/100; //(0~100 double)
    }
  }
  return;
}

// Transposta M
void transpostaM(double **M, int l, int c){
  int i, j;
  double aux;
  for (i = 0; i < l; i++) {
      for (j = i+1; j < c; j++) {
          aux = M[i][j];
          M[i][j] = M[j][i];
          M[j][i] = aux;
      }
  }
  return;
}

// Aloca Matriz lxc
double **alocaMatriz(int l, int c){
  int i;
  double **A;
  A = (double **) calloc(l, sizeof(double *));
  for(i = 0; i < l; i++)
    A[i] = (double *) calloc(c, sizeof(double));

  return A;
}

void Mult_Matriz(double **M1, double **M2, double **M3, int l, int c){

  for (int i=0;i<l; i++) {
      for (int j=0; j<l; j++) {
          M3[i][j] = 0;
          for (int k=0; k<c; k++) {
              M3[i][j] = M3[i][j] + (M1[i][k] * M2[k][j]);
          }
      }
  }
  return;

}

void Mult_Matriz_Transposta(double **M1, double **M2, double **M3, int l, int c){

  for (int i=0;i<l; i++) {
      for (int j=0; j<l; j++) {
          M3[i][j] = 0;
          for (int k=0; k<c; k++) {
              //printf("%.1lf = %.1lf * %.1lf ", M3[i][j], M[i][k], M2[j][k] );
              M3[i][j] = M3[i][j] + (M1[i][k] * M2[j][k]);
              //printf("%.1lf = %.1lf * %.1lf \n", M3[i][j], M1[i][k], M2[j][k] );
          }
      }
  }
  return;

}

// Coversão de nanosegundo para segundo
double timespecToSec(struct timespec *time){
    return (double)(time->tv_sec * 1000000000 + time->tv_nsec)/1000000000.0;
}


// compilar: gcc Mult_Matriz.c -o Mult_Matriz
// executar: ./Mult_Matriz
int main(int argc, char *argv[]){
   int i;
   struct timespec startWALL, endWALL, StartTransposta, EndTransposta, StartMultiTransposta, EndMultiTransposta;
   int linhas = atoi(argv[1]);
   int colunas = atoi(argv[2]);
   char tipo = *argv[3];
   printf("linhas: %d \n", linhas);
   printf("colunas: %d \n", colunas);
   printf("tipo: %c \n", tipo);


   if(*argv[3] == 'o'){
     double **MatA =  alocaMatriz(linhas,colunas);
     geraMatriz(MatA,linhas,colunas);
     PrintMatriz(MatA,linhas,colunas);

     double **MatB =  alocaMatriz(linhas,colunas);
     geraMatriz(MatB,linhas,colunas);
     PrintMatriz(MatB,linhas,colunas);

     double **MatC =  alocaMatriz(linhas,colunas);
     clock_gettime(CLOCK_MONOTONIC,&startWALL);
     Mult_Matriz(MatA, MatB, MatC, linhas, colunas);
     clock_gettime(CLOCK_MONOTONIC,&endWALL);
     PrintMatriz(MatC,linhas,colunas);
     double timeWALL = timespecToSec(&endWALL) - timespecToSec(&startWALL);
     printf("Tempo = %lf segundos\n", timeWALL);

     free(MatA);
     free(MatB);
     free(MatC);
   }

   if(*argv[3] == 't'){
     double **MatA =  alocaMatriz(linhas,colunas);
     geraMatriz(MatA,linhas,colunas);
     PrintMatriz(MatA,linhas,colunas);

     double **MatB =  alocaMatriz(linhas,colunas);
     geraMatriz(MatB,linhas,colunas);
     PrintMatriz(MatB,linhas,colunas);
     clock_gettime(CLOCK_MONOTONIC,&StartTransposta);
     transpostaM(MatB,linhas,colunas);
     clock_gettime(CLOCK_MONOTONIC,&EndTransposta);
     PrintMatriz(MatB,linhas,colunas);
     double TimeTransposta = timespecToSec(&EndTransposta) - timespecToSec(&StartTransposta);
     printf("Tempo = %lf TimeTransposta segundos\n", TimeTransposta);


     double **MatC =  alocaMatriz(linhas,colunas);
     clock_gettime(CLOCK_MONOTONIC,&StartMultiTransposta);
     Mult_Matriz_Transposta(MatA, MatB, MatC, linhas, colunas);
     clock_gettime(CLOCK_MONOTONIC,&EndMultiTransposta);
     PrintMatriz(MatC,linhas,colunas);
     double TimeMultiTransposta = timespecToSec(&EndMultiTransposta) - timespecToSec(&StartMultiTransposta);
     printf("Tempo = %lf TimeMultiTransposta segundos\n", TimeMultiTransposta);

     printf("Tempo = %lf TimeMultiTransposta + TimeTransposta segundos\n", (TimeMultiTransposta + TimeTransposta));


     free(MatA);
     free(MatB);
     free(MatC);

   }



}
