// Nomes dos Integrantes - NºUSP:
// André Campanholo Paschoalini - 14558061
// Eduardo Poltroniere da Silva - 16862892
// Enzo Trulenque Evangelista - 15819219
// Pedro Hamamoto da Palma - 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph
{
  int size;
  int **adj;
} GRAPH;

GRAPH *MyGraph(int size)
{
  GRAPH *graph = malloc(sizeof(GRAPH));

  int **adj = malloc(size * sizeof(int *));

  // Encerra a função se houver problemas na alocação do grafo ou das colunas da
  // matriz de adjacência
  if (graph == NULL || adj == NULL)
  {
    free(graph);
    free(adj);

    return NULL;
  }

  // Aloca memória para todas as linhas da matriz de adjacência
  for (int i = 0; i < size; i++)
  {
    // Aloca memória para a linha atual
    adj[i] = malloc(size * sizeof(int));

    if (adj[i] == NULL)
    {
      // Se não for possível alocar a linha, todo o grafo é liberado da memória
      for (int j = 0; j < i; j++)
        free(adj[j]);

      free(adj);
      free(graph);

      return NULL;
    }
    else
    {
      // Define todas os pesos como -1
      for (int j = 0; j < size; j++)
        adj[i][j] = -1;
    }
  }

  graph->size = size;
  graph->adj = adj;

  return graph;
}

void delete_graph(GRAPH **graph)
{
  if (graph != NULL && *graph != NULL)
  {
    // Libera as linhas da matriz de adjacência da memória
    for (int i = 0; i < (*graph)->size; i++)
      free((*graph)->adj[i]);

    // Libera as colunas da matriz de adjacência da memória
    free((*graph)->adj);

    free(*graph);

    *graph = NULL;
  }
}

void add_edge(GRAPH *graph, int node1, int node2, int weight)
{
  if (graph == NULL)
    return;

  graph->adj[node1][node2] = weight;
  graph->adj[node2][node1] = weight;
}

int remove_edge(GRAPH *graph, int node1, int node2)
{
  if (graph->adj[node1][node2] && graph != NULL)
  {
    graph->adj[node1][node2] = -1;
    graph->adj[node2][node1] = -1;
    return 1;
  }
  return -1;
}

bool exist_edge(GRAPH *graph, int node1, int node2)
{
  if (graph == NULL)
    return false;

  return graph->adj[node1][node2] != -1;
}

int *neighbors(GRAPH *graph, int node)
{
  if (graph == NULL)
    return NULL;

  int neighbors_amt = 0;

  for (int i = 0; i < graph->size; i++)
    neighbors_amt += graph->adj[node][i] != -1;

  int *neighbors_array = malloc((neighbors_amt + 1) * sizeof(int));

  if (neighbors_array == NULL)
    return NULL;

  int neighbors_found = 0;
  for(int i = 0; i < graph->size; i++)
  {
    if (graph->adj[node][i] != -1)
    {
      neighbors_array[neighbors_found] = i;
      neighbors_found++;
    }
  }
  neighbors_array[neighbors_found] = -1;
  return neighbors_array;
}

void print_info(GRAPH *graph)
{
  if (graph == NULL)
    return;

  printf("V = [");

  for (int i = 0; i < graph->size - 1; i++)
    printf("%d, ", i + 1);

  printf("%d]\n", graph->size);

  printf("E = [");

  bool foundEdge = false;

  for (int i = 0; i < graph->size; i++)
  {
    for (int j = i; j < graph->size; j++)
    {
      if (graph->adj[i][j] != -1)
      {
        if (foundEdge)
          printf(", ");

        printf("(%d, %d)", i, j);

        foundEdge = true;
      }
    }
  }

  printf("]\n");
}

int max_neighbors(GRAPH *graph)
{
  if (graph == NULL)
    return -1;

  int max_nbs = -1, max_node = -1, cur;

  for (int i = 0; i < graph->size; i++)
  {
    cur = 0;

    for (int j = 0; j < graph->size; j++)
    {
      cur += graph->adj[i][j] != -1;
    }

    if (cur > max_nbs)
    {
      max_nbs = cur;
      max_node = i;
    }
  }

  return max_node;
}

int **adjacency_matrix(GRAPH *graph)
{
  if (graph == NULL)
    return NULL;

  int **adj = malloc(graph->size * sizeof(int *));

  if (adj == NULL)
    return NULL;

  // Aloca memória para todas as linhas da matriz de adjacência
  for (int i = 0; i < graph->size; i++)
  {
    // Aloca memória para a linha atual
    adj[i] = malloc(graph->size * sizeof(int));

    if (adj[i] == NULL)
    {
      // Se não for possível alocar a linha, todo o grafo é liberado da memória
      for (int j = 0; j < i; j++)
        free(adj[j]);

      free(adj);

      return NULL;
    }
    else
    {
      // Copia os valores da matriz original
      for (int j = 0; j < graph->size; j++)
        adj[i][j] = graph->adj[i][j];
    }
  }

  return adj;
}

int main(void)
{
  int option;
  int N, x, y, w;
  int res;
  bool print_status = 0;

  GRAPH *G;

  scanf("%d", &option);

  while (option != -1)
  {
    switch (option)
    {
    case 0:
      scanf("%d", &N);
      G = MyGraph(N);
      print_status = 1;
      break;
    case 1:
    {
      // Adiciona-se uma aresta com seu respectivo peso
      scanf("%d %d %d", &x, &y, &w);
      add_edge(G, x, y, w);
      print_status = 1;
      break;
    }
    case 2:
      scanf("%d %d", &x, &y);
      res = exist_edge(G, x, y);
      print_status = 0;
      break;
    case 3:
      // vizinhos do nó lido
      scanf("%d", &x);
      int *v_vizinhos = neighbors(G, x);
      int i = 0;
      while(v_vizinhos[i] != -1){
        printf("%d ", v_vizinhos[i]);
        i++;
      }
      printf("\n");
      break;
    case 4:
      scanf("%d %d", &x, &y);
      if (!remove_edge(G, x, y))
        printf("-1");
      else print_status = 1;
      break;
    default:
      printf("unrecognized option %d!\n", option);
    }
    scanf("%d\n", &option);
  }

  if (print_status)
    print_info(G);
  else
    printf("%d\n", res);

  delete_graph(&G);
  return 0;
}
