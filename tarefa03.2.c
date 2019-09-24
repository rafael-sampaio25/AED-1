#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTAM 65536 // 2^16 //

typedef struct SCelula Celula;

struct SCelula{
  int Indice, Forca, ForcaI;
  Celula *prox;
};

typedef struct{
  Celula *frente, *tras;
  int tamanho;
}TFila;

void CriaFila(TFila *Fila){
  Fila->frente = NULL;
  Fila->tras = NULL;
  Fila->tamanho = 0;
}

int Enfileira(TFila *Fila, int Indice, int Forca, int ForcaI){
  Celula *novo = (Celula *) malloc(sizeof(Celula)); 

  novo->prox = NULL;
  novo->Indice = Indice;     // CRIANDO NOVA CELULA //
  novo->Forca = Forca;
  novo->ForcaI = ForcaI;
  if (Fila->tamanho == 0){ 
  
  // CASO NÃO EXISTA NINGUÉM NA FILA, O PRIMEIRO ELEMENTO SERÁ AO MESMO TEMPO, A CELULA DA FRENTE E TRÁS DA MINHA FILA //
    Fila->frente = novo;

  }else{
    
    // CASO CONTRÁRIO, ELA SERÁ APENAS A PRÓXIMA DA ÚLTIMA CELULA DA FILA //
    Fila->tras->prox = novo;

  }
  Fila->tras = novo; // ATUALIZANDO O FINAL DA MINHA FILA //
  Fila->tamanho++;
  return 1;
}

int Desenfileira(TFila *Fila, int *Indice, int *Forca, int *ForcaI){
  Celula *Aux;
  if (Fila->tamanho == 0){
    return 0;  // FILA VAZIA //
  }
  Aux = Fila->frente;
  *Indice = Fila->frente->Indice;
  *Forca = Fila->frente->Forca;
  *ForcaI = Fila->frente->ForcaI;
  Fila->frente = Fila->frente->prox;   // ATUALIZANDO A FRENTE DA MINHA FILA //
  Fila->tamanho--;  
  free(Aux);
  return 1;
}

int main(void){
  TFila Fila;
  int i, c, N, K, aux = 1, NPessoas;
  int Power, Forca;
  int Forca1, Forca2, Indice1, Indice2, ForcaI1, ForcaI2;
  CriaFila(&Fila);
  scanf("%d",&N);
  scanf("%d",&K);
  NPessoas = pow(2,N);
  for (i=0; i<NPessoas; i++){
    scanf("%d",&Forca);
    Enfileira(&Fila, Forca, i+1, Forca);
  }
  aux = 1;
  while (Fila.tamanho > 1){
    Desenfileira(&Fila, &Forca1, &Indice1, &ForcaI1);
    Desenfileira(&Fila, &Forca2, &Indice2, &ForcaI2);
    if (Forca1 >= Forca2){
      Power = (Forca1-Forca2)+K;
      if (Power<ForcaI1){
        Enfileira(&Fila, Power, Indice1, ForcaI1);
      }else{
        Enfileira(&Fila, ForcaI1, Indice1, ForcaI1);
      }
    }else{                            
      Power = (Forca2-Forca1)+K;
      if (Power<ForcaI2){
        Enfileira(&Fila, Power, Indice2, ForcaI2);
      }else{
        Enfileira(&Fila, ForcaI2, Indice2, ForcaI2);
      }
    }
  }
  aux *= 2;
  Desenfileira(&Fila, &Forca1, &Indice1, &ForcaI1);
  printf("%d\n",Indice1);
  return 0;
}
