#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTAM 32768 // 2^15 //

typedef struct SCelula Celula;

struct SCelula{
  int indice;
  float F, Finicial;
};

typedef struct{
  Celula participantes[MAXTAM];
  int frente, tras;
}TFila;

void Criafila(TFila *Fila){
  Fila->frente = 0;
  Fila->tras = Fila->frente;
}

Celula SetInfo(float x, int indice, float inicio){
    Celula *novo;
    novo = (Celula *) malloc(sizeof(Celula));
    novo->indice = indice;
    novo->F = x;
    novo->Finicial = inicio;
    return *novo;
}

int enfileira(TFila *Fila, Celula Novo){
  if (Fila->frente == (Fila->tras+1)%MAXTAM){
    // FILA CHEIA //
    return 0;
  }
  Fila->participantes[Fila->tras] = Novo;
  Fila->tras = (Fila->tras+1)%MAXTAM;
  return 1;
}

int desenfileira(TFila *Fila, Celula *X){
  if (Fila->frente == Fila->tras){
    // FILA VAZIA //
    return 0;
  }else{
    *X = Fila->participantes[Fila->frente];
    Fila->frente = (Fila->frente+1)%MAXTAM;
    return 1;
  }
}

int main(void){
  TFila Fila;
  Celula x1, x2;
  int i, c, N, K, aux = 1, NPessoas;
  float power, forca;
  Criafila(&Fila);
  scanf("%d",&N);
  scanf("%d",&K);
  NPessoas = pow(2,N);
  for (i=0; i<NPessoas; i++){
    scanf("%f",&forca);
    enfileira(&Fila, SetInfo(forca, i+1, forca));
  }
  aux = 1;
  for (c=0; c < N;c++){
    for (i=0; i < NPessoas/aux; i+=2){
      desenfileira(&Fila, &x1);
      desenfileira(&Fila, &x2);
      if (x1.F >= x2.F){
        power = (x1.F-x2.F)+K;
        if (power<x1.Finicial){
          enfileira(&Fila, SetInfo(power, x1.indice, x1.Finicial));
        }else{
          enfileira(&Fila, SetInfo(x1.Finicial, x1.indice, x1.Finicial));
        }
      }else{                            
        power = (x2.F-x1.F)+K;
        if (power<x2.Finicial){
          enfileira(&Fila, SetInfo(power, x2.indice, x2.Finicial));
        }else{
          enfileira(&Fila, SetInfo(x2.Finicial, x2.indice, x2.Finicial));
        }
      }
    }
    aux *= 2;
  }
  desenfileira(&Fila, &x1);
  printf("%d\n",x1.indice);
  return 0;
}
