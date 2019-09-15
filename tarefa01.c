#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int NumAlunos, Indice;
  int *Matricula;
}Unidade;

typedef struct{
  Unidade Universidade;
  int Cod, AlunosParticipantes;
  double Participacao;
}Univ;

typedef struct{
  int *Alunos;
  int cap;
}Bloco;

int main(void) {
  Univ *Facul;
  Bloco *Blocos; 
  int NBlocos;
  int N, CapBloco, i, Cod=0, Mat=0, x;
  scanf("%d",&N);
  Facul = (Univ *) calloc(N, sizeof(Univ));
  for (i=0; i<N; i++){
    scanf("%d%d",&Facul[i].Cod, &Facul[i].Universidade.NumAlunos);
  }
  for (i=0; i<N; i++){
    Facul[i].Universidade.Matricula = (int *) calloc(Facul[i].Universidade.NumAlunos, sizeof(int));
  }
  for (i=0; i<N; i++){
    Facul[i].AlunosParticipantes = 0;
    Facul[i].Universidade.Indice = 0;
  }
  scanf("%d",&CapBloco);
  Blocos = (Bloco *) calloc(1, sizeof(Bloco));
  NBlocos = 0;
  Blocos[NBlocos].Alunos = (int *) calloc(CapBloco, sizeof(int)); // Alocando Memória ao Bloco
  Blocos[NBlocos].cap = 0;
  scanf("%d",&Cod);
  if (Cod != -1){
    scanf("%d",&Mat);
  }
  while (Cod != -1){
    for (i=0; i<N; i++){
      if (Facul[i].Cod == Cod){
        Facul[i].Universidade.Matricula[Facul[i].Universidade.Indice] = Mat;
        Facul[i].Universidade.Indice++;
        Facul[i].AlunosParticipantes++;
        if (Blocos[NBlocos].cap >= CapBloco){
          NBlocos++;
          Blocos = (Bloco *) realloc(Blocos, (NBlocos+1)*sizeof(Bloco));
          Blocos[NBlocos].Alunos = (int *) calloc(CapBloco, sizeof(int)); 
          Blocos[NBlocos].cap = 0;
        }
        Blocos[NBlocos].Alunos[Blocos[NBlocos].cap] = Mat;
        Blocos[NBlocos].cap++;
        break;
      }
    }
    scanf("%d",&Cod);
    if (Cod != -1){
      scanf("%d",&Mat);
    }
  }
  for (i=0; i<N; i++){
    Facul[i].Participacao = (Facul[i].AlunosParticipantes*1.0/Facul[i].Universidade.NumAlunos)*100.0;
  }
  double MenorParticipacao = Facul[0].Participacao;
  int IndiceMenorParticipacao = 0;
  for (i=1; i<N; i++){
    if(Facul[i].Participacao < MenorParticipacao){
      MenorParticipacao = Facul[i].Participacao;
      IndiceMenorParticipacao = i;
    }
  }
  printf("%d\n",Facul[IndiceMenorParticipacao].Cod);
  for (i=0; i < Facul[IndiceMenorParticipacao].Universidade.Indice; i++){
    printf("%d\n",Facul[IndiceMenorParticipacao].Universidade.Matricula[i]);
  }
  for (i=0; i<N; i++){
    free(Facul[i].Universidade.Matricula);
  }
  free(Facul);
  for (i=0; i<=NBlocos; i++){
    free(Blocos[i].Alunos);
  }
  free(Blocos);
  return 0;
}
