#include <stdio.h>
#include <stdlib.h> // malloc
#include "list.h"   // StartList, ReturnP
#define MAXN 9      // Number of Nodes
//    a b c d e f g s t
//    0 1 2 3 4 5 6 7 8

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
  int aux;
  int v;
  List = (ListT *) malloc(sizeof(ListT));
  StartList(List);

  for (v = 0; v < Graph->NumNodes; v++) {
    if (CheckEdge(Graph, u, v)) {
      aux = v;
      if (v == 7) aux = 18; // add 's'
      if (v == 8) aux = 19; // add 't'
      Add(List, ReturnP(List, List->length), aux); // 'Add' is a list.h function
    }
  }
  return List;
}


// Extra Functions
// 1
void PrintGraph(GraphT *Graph, char Nodes[]) {
  int u, v;
  int i = 0;
  printf("\n  ");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c ", Nodes[i]);
    i++;
  }
  i = 0;
  printf("\n");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c ", Nodes[i]);
    i++;
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
  if (u == 'h') u = 's';
  if (u == 'i') u = 't';
  printf("The node '%c' conects to", u);
  if (List->length == 0) {
    /* The Node 'u' hasn't adjacencies, because the list of u adjacencies is empty. */
    printf(" no one :c\n");
  } else {
    PrintList(List);
  }
}

/* EDGES
s a
s b
s d
a c
b d
b s
c d
c e
d e
d f
d t
e g
e t
g e
g t
t f
*/

int main(void) {
  GraphT Graph;
  StartGraph(&Graph, MAXN); // MAXN = 9
  int i, a, b, NEdges = 16;
  char u[16] = {'s','s','s','a','b','b','c','c','d','d','d','e','e','g','g','t'};
  char v[16] = {'a','b','d','c','d','s','d','e','e','f','t','g','t','e','t','f'};
  char Nodes[MAXN] = {'a','b','c','d','e','f','g','s','t'};
  for (i = 0; i < NEdges; i++) {
    if (u[i] == 's')
      u[i] = 'h';
    if (u[i] == 't')
      u[i] = 'i';
    if (v[i] == 's')     // Fixing the index
      v[i] = 'h';
    if (v[i] == 't')
      v[i] = 'i';

    a = u[i] % 97;
    b = v[i] % 97;

    AddEdge(&Graph, a, b, 1);
  }
  PrintGraph(&Graph, Nodes);

  char Node;
  printf("Chosse one node to analyze: ");
  scanf("%c", &Node);
  // ASCII - 97 | 98 | 99 | 100 | 101 | 102 | 103 | 104 | 105 |#| 115 | 116 |
  // % 97    0  | 1  |  2 |  3  |  4  |  5  |  6  |  7  |  8  |#| 18  | 19  |
  //         a  | b  |  c |  d  |  e  |  f  |  g  |  h  |  i  |#|  s  |  t  |
  
  Node = Node % 97;
  if (Node == 18) Node = 7;
  if (Node == 19) Node = 8;
  // if Node = 's', now Node = 'h'
  ListT *List;
  List = AdjList(&Graph, Node);
  /* The AdjList function starts a list, that's why I'm not start my list before */
  PrintAdj(List, Node);
  DestroyList(List);
  return 0;
}