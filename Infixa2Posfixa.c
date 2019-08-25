#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SCelula Celula;

struct SCelula{
    char dado;
    Celula *prox;
};

typedef struct{
    Celula *topo;
    int tamanho;
}TPilha;

void CriaPilha(TPilha *pPilha){
    pPilha->topo = NULL;
    pPilha->tamanho = 0;
}

int TamanhoPilha(TPilha *pPilha){
    return pPilha->tamanho;
}

int Push(TPilha *pPilha, char x){
    Celula *NovaCelula;
    NovaCelula = (Celula *) malloc(sizeof(Celula));
    NovaCelula->dado = x;
    NovaCelula->prox = pPilha->topo;
    pPilha->topo = NovaCelula;
    pPilha->tamanho++;
    return 1;
}

int Pop(TPilha *pPilha, char *pX){
    Celula *pAux;
    if (pPilha->tamanho == 0){
        return 0;
    }else{
        pAux = pPilha->topo;
        *pX = pAux->dado;
        pPilha->topo = pAux->prox;
        pPilha->tamanho--;
        free(pAux);
        return 1;
    }
}

void infixa2posfixa(char op[],TPilha *Pilha){
  int i;
  char x;
  for (i=0; i < strlen(op); i++){
    switch (op[i]){
      case ' ': break;
      case '^':{
        while (Pilha->topo != NULL && Pilha->topo->dado == '^'){
          Pop(Pilha, &x);
          printf("%c",x);
        }
        Push(Pilha,'^');
        break;
      }
      case '*':{
        while (Pilha->topo != NULL && (Pilha->topo->dado == '/' || Pilha->topo->dado == '*' || Pilha->topo->dado == '^')){
          Pop(Pilha, &x);
          printf("%c",x);
        }
        Push(Pilha,'*');
        break;
      }
      case '/':{
        while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^')){
          Pop(Pilha, &x);
          printf("%c",x);
        }
        Push(Pilha,'/');
        break;
      }
      case '+':{
        while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^' || Pilha->topo->dado == '+' || Pilha->topo->dado == '-')){
          Pop(Pilha, &x);
          printf("%c",x);
        }
        Push(Pilha,'+');
        break;
      }
      case '-':{
        while (Pilha->topo != NULL && (Pilha->topo->dado == '*' || Pilha->topo->dado == '/' || Pilha->topo->dado == '^' || Pilha->topo->dado == '+' || Pilha->topo->dado == '-')){
          Pop(Pilha, &x);
          printf("%c",x);
          }
        Push(Pilha,'-');
        break;
      }
      case '(':{
        Push(Pilha,'(');
        break;
      }
      case ')':{
        while(Pilha->topo != NULL && Pilha->topo->dado != '('){
          Pop(Pilha, &x);
          printf("%c",x);
        }
        Pop(Pilha, &x);
        break;
      }
      default:{
        printf("%c",op[i]);
        break;
      }
    }
  }
  while(Pilha->topo != NULL){
    Pop(Pilha, &x);
    printf("%c",x);
  }
}

int main (void){
  char op[20];
  TPilha Pilha;
  CriaPilha(&Pilha);
  scanf("%[^\n]s",op);
  infixa2posfixa(op,&Pilha);
  return 0;
}
