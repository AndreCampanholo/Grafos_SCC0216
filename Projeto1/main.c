#include "graph.h"
#include <stdio.h>

int main() {
  int option;
  int N, x, y, w;
  scanf("%d", &N);

  GRAPH *G;

  scanf("%d", &option);

  switch (option) {
  case 0:
    G = MyGraph(N);
  case 1: {
    scanf("%d %d %d", &x, &y, &w);
    add_edge(G, x, y, w);
    scanf("%d %d %d", &x, &y, &w);
    add_edge(G, x, y, w);
    scanf("%d %d %d", &x, &y, &w);
    add_edge(G, x, y, w);
    /* scanf("%d %d %d", &x, &y, &w); */
    /* add_edge(G, x, y, w); */
    break;
  }
  case 2:
    break;
  default:
    printf("unrecognized option!\n");
  }

  print_info(G);
  delete_graph(&G);
}
