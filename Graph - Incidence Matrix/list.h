typedef struct SCell Cell;

struct SCell{
  int Adj; // ADJACENCIES OF 'u' VERTEX
  Cell *prev, *next;
};

typedef struct{
  Cell *last;
  int length;
}ListT;

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


/* NOT NECESSARY A REMOVE FUNCTION
int Remove(ListT *List, Cell *p, int *Adj) {
  Cell *aux;
  if (List->tamanho == 0) {
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
}*/


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

// Extra Functions [2]
// 1
void PrintList(ListT *List) {
  Cell *aux = List->last->next->next;
  int Node;
  printf(": ");
  while (aux != List->last->next) { // aux != head of my list
    Node = 97 + aux->Adj;
    printf("%c ", Node);
    aux = aux->next;
  }
  printf("\n");
}

// 2
void DestroyList(ListT *List) {
  Cell *aux = List->last->next->next;
  while (aux->next != List->last->next) {
    aux = aux->next;
    free(aux->prev);
    List->length--;
  }
  free(aux);
}
