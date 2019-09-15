#include <stdio.h>
#include <string.h>
#define MAXTAM 50

typedef struct{
  int topo;
  float item[MAXTAM];
}TPilha;

void CriaPilha(TPilha *pPilha){
  pPilha->topo = 0;
}

int TamanhoPilha(TPilha *pPilha){
  return pPilha->topo;
}

int Push(TPilha *pPilha, float x){
  if (pPilha->topo == MAXTAM){
    return 0;
  }else{
    pPilha->item[pPilha->topo] = x;
    pPilha->topo++;
  return 1;
  }
}

int Pop(TPilha *pPilha, float *pX){
  if (pPilha->topo == 0){
    return 0;
  }else{
    pPilha->topo--;
    *pX = pPilha->item[pPilha->topo];
    return 1;
  }
}

void LerOP(TPilha *Pilha, char op[]){
  int i;
  float x=0, x1=0, x2=0, vet[25] = {0};
  for (i=0; i<strlen(op); i++){
    switch (op[i]){
      case '+': 
        Pop(Pilha, &x1);
        Pop(Pilha, &x2);
        x = x2 + x1;
        Push(Pilha, x);
        break;
      case '-': 
        Pop(Pilha, &x1);
        Pop(Pilha, &x2);
        x = x2 - x1;
        Push(Pilha, x);
        break;
      case '/': 
        Pop(Pilha, &x1);
        Pop(Pilha, &x2);
        x = x2 / x1;
        Push(Pilha, x);
        break;
      case '*': 
        Pop(Pilha, &x1);
        Pop(Pilha, &x2);
        x = x2 * x1;
        Push(Pilha, x);
        break;
      default: 
        scanf("%f",&x);
        Push(Pilha, x);
        break;
    }
  }
  printf("%f",x);
}

int main (void){
  TPilha Pilha;
  char op[MAXTAM];
  CriaPilha(&Pilha);
  scanf("%s", op);
  LerOP(&Pilha, op);
  return 0;
}