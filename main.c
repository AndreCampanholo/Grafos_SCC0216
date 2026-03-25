#include "graph.h"
#include <stdio.h>

int main(void)
{
  int option;
  int N, x, y, w;
  int res;
  bool print_status = -1;

  GRAPH *G;

  scanf("%d", &option);

  while (option != -1)
  {
    switch (option)
    {
    case 0:
      scanf("%d", &N);
      G = MyGraph(N);
      break;
    case 1:
    {
      // Adiciona-se uma aresta com seu respectivo peso
      scanf("%d %d %d", &x, &y, &w);
      add_edge(G, x, y, w);
      break;
    }
    case 2:
      scanf("%d %d", &x, &y);
      res = exist_edge(G, x, y);
      print_status = 0;
      break;
    default:
      printf("unrecognized option %d!\n", option);
    }
    scanf("%d\n", &option);
  }

  if (option != -1)
  {
    if (print_status)
      print_info(G);
    else
      printf("%d\n", res);
  }
  delete_graph(&G);
  return 0;
}
