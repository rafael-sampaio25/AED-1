// Não copia, valeu! <3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 100


typedef struct {
  int EdgeIndex;
  int Edge;
} Adjacency;

typedef struct {
  Adjacency Adj[MAXN][MAXN];
  int NumNodes;
  int NEdge;
} GraphT;

typedef struct SCell Cell;

struct SCell{
  int Adj; // ADJACENCIES OF 'u' VERTEX
  Cell *prev, *next;
};

typedef struct{
  Cell *last;
  int length;
}ListT;

// // // // // // // // // // // // //

void StartList(ListT *List) {
  List->last = (Cell *) malloc(sizeof(Cell));
  List->last->next = List->last;
  List->last->prev = List->last;
  List->length = 0;
}

int Add(ListT *List, Cell *p, int Adj) {
  Cell *new;
  if (p == NULL) {
    return 0;
  }
  new = (Cell *) malloc(sizeof(Cell));
  new->Adj = Adj;
  new->next = p;
  new->prev = p->prev;
  p->prev->next = new;
  if (p->prev == List->last) {
    List->last = new;
  }
  p->prev = new;
  List->length++;
  return 1;
}

int Remove(ListT *List, Cell *p, int *Adj) {
  Cell *aux;
  if (List->length == 0) {
    return 0;
  }
  aux = p;
  p->prev->next = p->next;
  p->next->prev = p->prev;
  if (aux == List->last) {
    List->last = p->prev;
  }
  *Adj = aux->Adj;
  free (aux);
  List->length--;
  return 1;
}

Cell *ReturnP(ListT *List, int p) {
  Cell *aux;
  if (p > List->length/2) {
    aux = List->last;
    int position = List->length-1;
    while (aux != List->last->next && position != p) {
      aux = aux->prev;
      position--;
    }
  } else {
    aux = List->last->next->next;
    int position = 0;
    while (aux != List->last->next && position != p) {
      aux = aux->next;
      position++;
    }
  }
  return aux;
}

void DestroyList(ListT *List) {
  Cell *aux = List->last->next->next;
  while (aux->next != List->last->next) {
    aux = aux->next;
    free(aux->prev);
    List->length--;
  }
  free(aux);
}

// // // // // // // // // // // // // //

int StartGraph(GraphT *Graph, int NumNodes) {
  int u, v; // Node
  if (NumNodes > MAXN) {
    return 0;
  }
  Graph->NumNodes = NumNodes;
  Graph->NEdge = 0;
  for (u = 0; u < Graph->NumNodes; u++) {
    for (v= 0; v < Graph->NumNodes; v++) {
      Graph->Adj[u][v].EdgeIndex = 0;
    }
  }
  return 1;
}

int CheckEdge(GraphT *Graph, int u, int v) {
  return Graph->Adj[u][v].EdgeIndex;
}

int AddEdge(GraphT *Graph, int u, int v, int e) {
  Graph->Adj[u][v].EdgeIndex = 1;
  Graph->Adj[u][v].Edge = e;
  Graph->NEdge++;
  return 1;
}

int RmvEdge(GraphT *Graph, int u, int v, int *e) {
  if (!CheckEdge(Graph, u, v)) {
    return 0;
  }
  *e = Graph->Adj[u][v].Edge;
  Graph->Adj[u][v].EdgeIndex = 0;
  Graph->NEdge--;
  return 1;
}

ListT *AdjList(GraphT *Graph, int u) {
  ListT *List;
  int v;
  List = (ListT *) malloc(sizeof(ListT));
  StartList(List);

  for (v = 0; v < Graph->NumNodes; v++) {
    if (CheckEdge(Graph, u, v)) {
      Add(List, ReturnP(List, List->length), v); // 'Add' is a list.h function
    }
  }
  return List;
}

int Dependents(GraphT *Graph, int v) {
    int u = 0, DependentsNumber = 0;
    for (u = 0; u < Graph->NumNodes; u++) {
        if (CheckEdge(Graph, u, v))
            DependentsNumber++;
    }
    return DependentsNumber;
}

int main(void) {
  GraphT Graph;
  int N, D;
  scanf("%d%d", &N, &D);
  StartGraph(&Graph, N);
  int i, u, v;
  int NewEdge = 1;
  for (i = 0; i < D; i++) {
    scanf("%d%d", &u, &v);
    AddEdge(&Graph, u - 1, v - 1, NewEdge);
  }
  ListT *List;
  for (i = 0; i < N; i++) {
      List = AdjList(&Graph, i);
      printf("%d %d %d", i + 1, Dependents(&Graph, i), List->length);

      while(Remove(List, ReturnP(List, 0), &v)) {
          printf(" %d", v + 1);
      }

      printf("\n");
      DestroyList(List);
  }
  return 0;
}
