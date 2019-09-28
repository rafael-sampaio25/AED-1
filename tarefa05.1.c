#include <stdio.h>
#include <string.h>

/*
typedef struct TCelula Celula;

struct TCelula{
  int dado;
};
NÃO SERÁ NECESSÁRIO UMA CÉLULA, POIS A ÚNICA 
VARIÁVEL QUE IREMOS TRABALHAR É CHAR. */

typedef struct{
  char Caractere[50000];
  int Primeiro, Ultimo, Tamanho;
}TLista;

void IniciaLista(TLista *Lista){
  Lista->Primeiro = 0;
  Lista->Ultimo = Lista->Primeiro;
  Lista->Tamanho = 0;
}

/*Celula SetInfo(int dado){
  Celula novo;
  novo.dado = dado;         
  return novo;              ESSA FUNÇÃO É UTILIZADA PARA, DADAS INFORMAÇÕES      
                            RECEBIDAS, RETORNAR ESSE VALOR DENTRO DE UMA CELULA.
                            PORÉM, COMO NÃO ESTAMOS UTILIZANDO UMA CELULA, NÃO 
                            UTILIZAREMOS ESSA FUNÇÃO, APESAR DE SER BASTANTE ÚTIL.
} */

int Insere(TLista *Lista, int p, char x){
  int q;
  if (Lista->Ultimo == 50000 || p < Lista->Primeiro || p > Lista->Ultimo){
    return 0;  // VERIFICA SE O ÍNDICE ONDE SERÁ INSERIDO O CHAR 'x' FAZ PARTE DA LISTA. // 
  }
  for (q=Lista->Ultimo-1; q >= p; q--){ 
    // ESTE FOR IRÁ DESLOCAR OS ITENS DA LISTA PARA LIBERAR O ESPAÇO PARA UM NOVO ITEM. //
    Lista->Caractere[q+1] = Lista->Caractere[q];
  }
  Lista->Caractere[p] = x; // APÓS O FOR, O ESPAÇO 'p' ESTÁ LIVRE, ENTÃO SERÁ INSERIDO O CHAR 'x' //
  Lista->Ultimo++; // INCREMENTA 1 NO ÍNDICE //
  Lista->Tamanho++;
  return 1;
}

int Retira(TLista *Lista, int p, char *pX){
  int q;
  if (Lista->Primeiro == Lista->Ultimo || p < Lista->Primeiro || p >= Lista->Ultimo){
    return 0; // VERIFICA SE O ÍNDICE ONDE SERÁ INSERIDO O CHAR 'x' FAZ PARTE DA LISTA. // 
  }
  *pX = Lista->Caractere[p]; 
  // ARMAZENA O ITEM QUE SERÁ RETIRADO, APESAR DE NÃO UTILIZARMOS ESTA FUNÇÃO NESSE PROGRAMA. //
  for (q=p+1; q<Lista->Ultimo; q++){
    Lista->Caractere[q-1] = Lista->Caractere[q]; 
    // ESTE FOR IRÁ DESLOCAR OS ITENS DA LISTA A FIM DE OCUPAR O ESPAÇO DE 'p'. //
  }
  Lista->Ultimo--; // COMO FOI RETIRADO UM ITEM, ENTÃO DIMINUÍRA O ÍNDICE. //
  Lista->Tamanho--;
  return 1;
}



// EXEMPLO DE ENTRADA:
// Bas--[ [o[i]asga-axx--lu[c[r[á[M]px-p
// SAÍDA:
// Márcio Basgalupp



int main(void){
  TLista Lista;
  IniciaLista(&Lista);
  int i, fraseTAM;
  char frase[50000], aux;
  for (i=0; ; i++){
    scanf("%c", &aux);
    if (aux == '\n'){ // SE O CARACTERE ATUAL FOR '\n', A LEITURA SERÁ INTERROMPIDA. // 
      break;
    }
    frase[i] = aux;
  }

// ANALISANDO A STRING //

  fraseTAM = strlen(frase); // A FUNÇÃO "strlen" RETORNA O TAMANHO DA MINHA STRING //
  
  int ind = 0;
  // 'ind' É O ÍNDICE ONDE SERÁ INSERIDO O ITEM NA LISTA //
  for (i=0; i<fraseTAM; i++){ // PERCORRENDO OS CARACTERES DA MINHA STRING //
    switch(frase[i]){
      case '[':
        ind = Lista.Primeiro; // 'ind' PASSA A SER O ÍNDICE DO Primeiro ITEM DA LISTA //
        break;
      case ']':
        ind = Lista.Ultimo;  // 'ind' PASSA A SER O ÍNDICE DO ÚLTIMO ITEM DA LISTA //
        break;
      case '-':
        if (ind > 0){
          ind--;  /* NO FINAL DE TODA INSERÇÃO DE DÍGITO É INCREMENTADO 
                  1 NO ÍNDICE. LOGO, PARA DELETARMOS O ÚLTIMO DÍGITO,
                  DEVEMOS, Primeiro, DIMINUIR O ÍNDICE.                */

          Retira(&Lista, ind, &aux); /* AUX APENAS SERVE PARA RECEBER O DÍGITO QUE
                                    IRÁ SER DELETADO. PORÉM NÃO SERÁ UTILIZADA
                                    ESSA FUNÇÃO NESSE PROGRAMA.  */
        }
        break;
      case '<':
        if (ind > 0){
          ind--; // A PRÓXIMA INSERÇÃO SERÁ ANTES DO ÚLTIMO DÍGITO //
        }
        break;
      case '>':
        if (ind < Lista.Tamanho){
          ind++; // A PRÓXIMA INSERÇÃO SERÁ DEPOIS DO PRÓXIMO DÍGITO //
        }
        break;
      default:
        Insere(&Lista, ind, frase[i]);
        ind++; // PASSA PARA O PRÓXIMO ÍNDICE //
        break;
    }
  }

  // IMPRIMINDO OS CARACTERES DA LISTA //

  for (i=0; i<Lista.Ultimo; i++){
    printf("%c",Lista.Caractere[i]);
  }
  return 0;
}
