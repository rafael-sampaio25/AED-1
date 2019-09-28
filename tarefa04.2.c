#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SCelula celula;

struct SCelula{
  char nome[20];
  celula *ant, *prox;
};

typedef struct{
  celula *ultimo;
  int tamanho;
}TLista;

void CriaLista(TLista *Lista){
  Lista->ultimo = (celula *) malloc(sizeof(celula));
  Lista->ultimo->prox = Lista->ultimo;
  Lista->ultimo->ant = Lista->ultimo;
  Lista->tamanho = 0;
}

int Insere(TLista *Lista, celula *p, char nome[]){
  celula *novo;
  if (p == NULL){
    return 0;
  }
  novo = (celula *) malloc(sizeof(celula));
  strcpy(novo->nome, nome);
  novo->prox = p;
  novo->ant = p->ant;
  p->ant->prox = novo;
  if (p->ant == Lista->ultimo){
    Lista->ultimo = novo;
  }
  p->ant = novo;
  Lista->tamanho++;
  return 1;
}


int Retira(TLista *Lista, celula *p, char nome[]){
  celula *aux;
  if (Lista->tamanho == 0){
    return 0;
  }
  aux = p;
  p->ant->prox = p->prox;
  p->prox->ant = p->ant;
  if (aux == Lista->ultimo){
    Lista->ultimo = p->ant;
  }
  strcpy(nome, aux->nome);
  free (aux);
  Lista->tamanho--;
  return 1;
}

celula *RetornaP(TLista *Lista, int p){
  celula *aux;
  aux = Lista->ultimo->prox->prox;
  int posicao = 0;
  while (aux != Lista->ultimo->prox && posicao != p){
    aux = aux->prox;
    posicao++;
  }
  return aux;
}
/* OBS: MESMA TAD DOS SLIDES. APENAS HÁ ALTERAÇÕES NOS NOMES DA 
   VARIÁVEIS COM OBJETIVO DE MELHORAR O ENTENDIMENTO DA LISTA DUPLA.*/ 



void LeNome(TLista *Lista, int N){
  int i;
  char nome[20];
  for (i=0; i<N; i++){
    scanf("%s",nome);
    Insere(Lista, RetornaP(Lista, i), nome);
  }
}

void Brincadeira(TLista *Lista, int N, int K){
  int ValorinicialK = K;
  char nome[20];
  while (Lista->tamanho != 0){
    K = K % Lista->tamanho; 
    Retira(Lista, RetornaP(Lista, K), nome);
    K += ValorinicialK;
    printf("%s\n", nome);
  }
}



int main(void){
  TLista Lista;
  int N, K;
  scanf("%d%d",&N,&K);
  CriaLista(&Lista);
  LeNome(&Lista, N);
  Brincadeira(&Lista, N, K);
  return 0;
}
