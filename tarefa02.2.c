#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 50

typedef struct TCelula Celula;

// CELULA QUE ARMAZENA UMA VARIÁVEL FLOAT E UM APONTADOR PROXIMO //
struct TCelula{
  float item;
  Celula *prox;  // POR SER DO TIPO CELULA, ELA IRÁ APONTAR PARA UMA VARIÁVEL DO TIPO CÉLULA //
};
 

/* ESTRUTURA ONDE SERÁ ARMAZENADA AS INFORMAÇÕES
   PRINCIPAIS DA MINHA PILHA, SENDO ELAS, O TOPO
   DA MINHA PILHA E O TAMANHO DA MESMA.        */
typedef struct{
  Celula *topo;
  int tamanho;
}TPilha;

// CRIAÇÃO DA PILHA // 
void CriaPilha(TPilha *pPilha){
  pPilha->topo = NULL;  // DEFININDO O TOPO INICIAL COMO "NULL" //
  pPilha->tamanho = 0;
}

// EMPILHANDO // FUNÇÃO PUSH == FUNÇÃO EMPILHAR //
int Push(TPilha *pPilha, float x){
  Celula *NovaCelula; // CRIAÇÃO DE UMA NOVA CELULA //

  // ALOCAÇÃO UM ESPAÇO DE MEMÓRIA DO TIPO CELULA PARA MINHA NOVA VARIÁVEL //
  NovaCelula = (Celula *) malloc(sizeof(Celula));

  // O ITEM DA MINHA NOVA CÉLULA SERÁ O ITEM RECEBIDO COMO PARAMÊTRO NA FUNÇÃO//
  NovaCelula->item = x;     
  NovaCelula->prox = pPilha->topo; // 1º PASSO: ADERINDO O PRÓXIMO DA MINHA PILHA COMO O MEU ANTIGO TOPO DA PILHA //
  pPilha->topo = NovaCelula;       // 2º PASSO: ATUALIZANDO O TOPO DA MINHA PILHA PARA A NOVA CELULA //
  pPilha->tamanho++; // AUMENTO NO NÚMERO DE CÉLULAS NA PILHA //
  return 1;
}

 
// DESEMPILHANDO // FUNÇÃO POP = FUNÇÃO DESEMPILHAR //
int Pop(TPilha *pPilha, float *pX){

  /* NESTA FUNÇÃO, COMO IREMOS TIRAR UMA CELULA DA NOSSA PILHA, 
     PRECISAREMOS LIBERAR O ESPAÇO DE MEMÓRIA QUE ESTA CELULA
     ESTAVA UTILIZANDO, PARA ISSO IREMOS UTILIZAR O VARIÁVEL
     AUXILIAR DO MESMO TIPO CHAMADA DE "AUX".                    */
  Celula *Aux;
  if (pPilha->tamanho == 0){ // VERIFICA SE A PILHA POSSUI ELEMENTOS
    return 0;
  }
  Aux = pPilha->topo;
  *pX = Aux->item; // IREMOS ALTERAR O VALOR DO ENDEREÇO DE MEMÓRIA QUE "*pX" APONTA //
  pPilha->topo = Aux->prox; // ATUALIZANDO MEU TOPO //
  free(Aux); // LIBERANDO O ESPAÇO DE MEMÓRIA QUE MINHA ANTIGA CÉLULA UTILIZAVA //
  pPilha->tamanho--;
  return 1;
}
 


// FUNÇÃO QUE ANALISA MINHA OPERAÇÃO E IMPRIME O RESULTADO DA MESMA //
void LerOP(TPilha *Pilha, char op[]){
  int i;
  float x=0, x1=0, x2=0;

  // IREMOS ANALISAR CADA CARACTERE DA STRING //
  for (i=0; i<strlen(op); i++){   /* A FUNÇÃO STRLEN( ) RECEBE COMO PARÂMETRO UMA STRING E 
                                     RETORNA O TAMANHO DA MESMA, SENDO ASSIM, A VARIÁVEL 'i',
                                     IRÁ PERCORRER TODOS OS CARACTERES DE NOSSA STRING         */

    switch (op[i]){   // op[i] É O CARACTERE NO ÍNDICE 'i' DA MINHA STRING //

    /* HÁ 2 POSSÍVEIS CASOS, O CASO QUE O CARACTERE EM QUESTÃO É
       UM SINAL DE OPERAÇÃO E O CASO EM QUE O CARACTERE É UMA LETRA:

       - QUANDO ENCONTRAR UMA LETRA A FUNÇÃO IRÁ LER UMA VARIÁVEL
       DO TIPO FLOAT E IRÁ EMPILHAR ESSA VARIÁVEL. EX:
        EM UMA STRING "ABC+*" O PRIMEIRO CARACTERE A SER ANALISADO
       É O 'A', QUANDO A FUNÇÃO ANALISAR 'A', ELA IRÁ LER UM VALOR
       FLOAT E INSERIR EM UMA VARIÁVEL 'x' E, EM SEGUIDA, ESSA
       VARIÁVEL SERÁ EMPILHADA.

       - QUANDO ENCONTRAR UM SINAL DE OPERAÇÃO, ELA IRÁ DESEMPILHAR
       OS DOIS ULTIMOS VALORES DA PILHA E IRÁ FAZER A OPERAÇÃO COM
       ELES, SENDO O SEGUNDO VALOR DESEMPILHADO A SER SEMPRE O OPERANDO
       DA ESQUERDA. EX:
        1º VALOR DESEMPILHADO = 3; 
        2º VALOR DESEMPILHADO = 5;
        PORTANTO, EM UMA DIVISÃO SERÁ REALIZADA A OPERAÇÃO 5/3.

       APÓS A OPERAÇÃO, SERÁ EMPILHADO O RESULTADO DA OPERAÇÃO.            */


      case '+': 
        Pop(Pilha, &x1); // x1 É O 1º VALOR A SER DESEMPILHADO //
        Pop(Pilha, &x2); // x2 É O 2º VALOR A SER DESEMPILHADO //
        x = x2 + x1;     // OPERAÇÃO: x2 + x1                  //
        Push(Pilha, x);  // EMPILHANDO O RESULTADO DA OPERAÇÃO //
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

    /* CASO DEFAULT É O CASO DE QUALQUER CARACTERE 
       EXCETO OS DAS OPERAÇÕES EM QUESTÃO.         */
      default: 
        scanf("%f",&x); // LENDO UM VALOR PARA O CARACTERE //
        Push(Pilha, x); // EMPILHANDO O VALOR // 
        break;
    }
  }
/* DEPOIS DE ANALISAR A OPERAÇÃO SERÁ DESEMPILHADO
   O ÚNICO VALOR RESTANTE DA PILHA, SENDO ELE O
   RESULTADO DEFINITIVO DA MINHA OPERAÇÃO.         */
  Pop(Pilha, &x1); 
  printf("%f", x1);
}
 
int main (void){
  TPilha Pilha;
  char op[MAXTAM]; // MAXTAM == 50 //
  CriaPilha(&Pilha);
  scanf("%s", op);
  LerOP(&Pilha, op);
  return 0;
}
