#include <stdio.h>
#include <string.h>
#define INICIO 0
#define MAXTAM 1000

typedef struct TCelula Celula;

struct TCelula{
  char nome[20];
};

typedef struct{
  Celula item[MAXTAM];
  int primeiro, ultimo;
}TLista;

void CriaLista(TLista *Lista){
  Lista->primeiro = INICIO;
  Lista->ultimo = Lista->primeiro;
}

Celula SetInfo(char nome[]){
  Celula novo;
  strcpy(novo.nome, nome);
  return novo;
}

int Insere(TLista *Lista, int p, Celula x){
  int q;
  if (Lista->ultimo == MAXTAM || p < Lista->primeiro || p > Lista->ultimo){
    return 0;
  }
  for (q=Lista->ultimo-1; q >= p; q--){
    Lista->item[q+1] = Lista->item[q];
  }
  Lista->item[p] = x;
  Lista->ultimo++;
  return 1;
}

int Retira(TLista *Lista, int p, Celula *pX){
  int q;
  if (Lista->primeiro == Lista->ultimo || p < Lista->primeiro || p >= Lista->ultimo){
    return 0;
  }
  *pX = Lista->item[p];
  for (q=p+1; q<Lista->ultimo; q++){
    Lista->item[q-1] = Lista->item[q];
  }
  Lista->ultimo--;
  return 1;
}

int main(void){
  TLista Lista;
  Celula x;
  int i, N, K, aux;
  char nome[20];
  CriaLista(&Lista);
  scanf("%d%d",&N,&K);
  for (i=0; i<N; i++){
    scanf("%s",nome);   // Laço de repetição para ler o nome da cada criança;
    Insere(&Lista, i, SetInfo(nome));
  }
  int ValorinicialK = K;
  aux = Lista.ultimo;
  for (i=0; i<N; i++){
    Retira(&Lista, K%aux, &x);
    K = K%aux;
    K += ValorinicialK; // Somando sempre o valor inicial de K, visto que neste ciclo o valor de K iria mudar constantemente.
    aux--;
    printf("%s\n",x.nome);
  }
  return 0;
}
