#include <stdio.h>
#include <stdlib.h> // malloc, rand, srand
#include <time.h>   // time;
#include "list.h"   // StartList, ReturnP
#define MAXN 5      // Number of Nodes
#define MAXE 100    // Number of Edges
//    a b c d e
//    0 1 2 3 4

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
  int v; // node
  int e; // edge
  List = (ListT *) malloc(sizeof(ListT));
  StartList(List);
  for (e = 0; e < Graph->NEdge; e++) {
    if (Graph->Adj[u][e].EdgeIndex > 0) {
      for (v = 0; v < Graph->NumNodes; v++) {
        if (Graph->Adj[v][e].EdgeIndex < 0) {
          Add(List, ReturnP(List, List->length), v);
          break;
        }
      }
    }
  }
  return List;
}


// Extra Functions
// 1
void PrintGraph(GraphT *Graph) {
  int u, v;
  int e = 1;
  char actualV = 'a'; // ASCCI - 97 - 'a'
  printf("\n  ");
  for (u = 0; u < Graph->NEdge; u++) {
    printf("e%d ", e);
    e++;
  }
  printf("\n");
  for (u = 0; u < Graph->NumNodes; u++) {
    printf("%c ", actualV);
    actualV++;
    for (v = 0; v < Graph->NEdge; v++) {
      if (Graph->Adj[u][v].EdgeIndex != -1) {
        printf(" ");
      }
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
    //The Node 'u' hasn't adjacencies, because the list of u adjacencies is empty.
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
  printf("\n u   v\n");
  for (i = 0; i < 5; i++) {
    u = rand()%MAXN;
    v = rand()%MAXN;
    AddEdge(&Graph, u, v, 3);
    printf(" %c | %c  -->  e%d\n", u+97, v+97, i+1);
  }
  PrintGraph(&Graph);

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
