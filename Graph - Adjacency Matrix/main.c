#include <stdio.h>
#include <stdlib.h> // malloc, rand, srand
#include <time.h>   // time;
#include "list.h"   // StartList, ReturnP
#define MAXN 5      // Number of Nodes
//    a b c d e
//    0 1 2 3 4

typedef struct {
  int EdgeIndex;
  int Edge;
} Adjacency;

typedef struct {
  Adjacency Adj[MAXN][MAXN];
  int NumNodes;
  int NEdge;
} GraphT;

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


// Extra Functions
// 1
void PrintGraph(GraphT *Graph) {
  int u, v;
  char actualV = 'a'; // ASCCI - 97 - 'a'
  printf("\n  ");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c ", actualV);
    actualV++;
  }
  actualV = 'a';
  printf("\n");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c ", actualV);
    actualV++;
    for (v = 0; v < Graph->NumNodes; v++) {
      printf("%d ", Graph->Adj[u][v].EdgeIndex);
    }
    printf("\n");
  }
  printf("\n");
}

// 2
void PrintAdj(ListT *List, int Node) {
  char u = Node + 97;
  printf("The node '%c' conects to", u);
  if (List->length == 0) { 
    /* The Node 'u' hasn't adjacencies, because the list of u adjacencies is empty. */
    printf(" no one :c\n"); 
  } else {
    PrintList(List); 
  }
}



int main(void) {
  GraphT Graph;
  StartGraph(&Graph, MAXN);
  int i, u, v;
  srand(time(NULL));
  for (i = 0; i < MAXN; i++) {
    AddEdge(&Graph, rand()%MAXN, rand()%MAXN, 3);
//         (*Graph,      u     ,      v     , e)
  }
  
  PrintGraph(&Graph);
  
  /*
  u = 1; v = 2;
  if (CheckEdge(&Graph, u, v)) {
    printf("There is an edge between the Nodes %d and %d\n", u, v);
  } else {
    printf("There is no edge between the Nodes %d and %d\n", u, v);
  }
  */
  char Node;
  printf("Chosse one node to analyze: ");
  scanf("%c", &Node); 
  // ASCII - 97 | 98 | 99 | 100 | 101
  //         a  | b  |  c |  d  |  e
  Node = Node % 97;
  // if Node = 'd', now Node = 3
  ListT *List;
  List = AdjList(&Graph, Node);
  /* The AdjList function starts a list, that's why I'm not start my list before */
  PrintAdj(List, Node);
  DestroyList(List);
  return 0;
}
