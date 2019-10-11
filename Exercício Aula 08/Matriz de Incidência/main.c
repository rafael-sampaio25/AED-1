#include <stdio.h>
#include <stdlib.h> // malloc
#include "list.h"   // StartList, ReturnP
#define MAXN 9     // Number of Nodes
#define MAXE 16    // Number of Edges
//    a b c d e f g s t
//    0 1 2 3 4 5 6 7 8

typedef struct {
  int EdgeIndex;
  int Edge;
} Adjacency;

typedef struct {
  Adjacency Adj[MAXN][MAXE];
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
  return 1;
}

int CheckEdge(GraphT *Graph, int u, int v) {
  int e;
  for (e = 0; e < Graph->NEdge; e++) {
    if ((Graph->Adj[u][e].EdgeIndex > 0) && (Graph->Adj[v][e].EdgeIndex < 0)) {
      return 1;
    }
  }
  return 0;
}

int AddEdge(GraphT *Graph, int u, int v, int e) {
  int i;
  if (Graph->NEdge >= MAXE) {
    return 0;
  }
  for (i = 0; i < Graph->NumNodes; i++) {
    Graph->Adj[i][Graph->NEdge].EdgeIndex = 0;
  }
  if (u != v) {
    Graph->Adj[u][Graph->NEdge].EdgeIndex = 1;
    Graph->Adj[v][Graph->NEdge].EdgeIndex = -1;
    Graph->Adj[u][Graph->NEdge].Edge = e;
    Graph->Adj[v][Graph->NEdge].Edge = e;
  } else {
    Graph->Adj[u][Graph->NEdge].EdgeIndex = 2;
  }

  Graph->NEdge++;
  return 1;
}

int RmvEdge(GraphT *Graph, int u, int v, int *pE) {
  int i;
  int e;
  if (!CheckEdge(Graph, u, v)) {
    return 0;
  }
  for (e = 0; e < Graph->NEdge; e++) {
    if (Graph->Adj[u][e].EdgeIndex > 0 && Graph->Adj[v][e].EdgeIndex < 0) {
      break;
    }
  }
  *pE = Graph->Adj[u][e].Edge;
  for (i = 0; i < Graph->NumNodes; i++) {
    Graph->Adj[i][e] = Graph->Adj[i][Graph->NEdge-1];
  }
  Graph->NEdge--;
  return 1;
}

ListT *AdjList(GraphT *Graph, int u) {
  ListT *List;
  int aux;
  int v; // node
  int e; // edge
  List = (ListT *) malloc(sizeof(ListT));
  StartList(List);
  for (e = 0; e < Graph->NEdge; e++) {
    if (Graph->Adj[u][e].EdgeIndex > 0) {
      for (v = 0; v < Graph->NumNodes; v++) {
        if (Graph->Adj[v][e].EdgeIndex < 0) {
          aux = v;
          if (v == 7) aux = 18; // add 's'
          if (v == 8) aux = 19; // add 't'
          Add(List, ReturnP(List, List->length), aux);
          break;
        }
      }
    }
  }
  return List;
}


// Extra Functions
// 1
void PrintGraph(GraphT *Graph, char Nodes[]) {
  int u, v;
  printf("\n   ");
  for (u = 0; u < Graph->NEdge; u++) {
    if (u > 10) printf(" ");
    printf("e%d  ", u+1);
  }
  printf("\n");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c  ", Nodes[u]);
    for (v = 0; v < Graph->NEdge; v++) {
      if (Graph->Adj[u][v].EdgeIndex != -1) printf(" ");
      if (v > 10) printf("  ");
      printf("%d  ", Graph->Adj[u][v].EdgeIndex);
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
  StartGraph(&Graph, MAXN);
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