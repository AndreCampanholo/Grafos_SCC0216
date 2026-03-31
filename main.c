// Nomes dos Integrantes - NºUSP:
// André Campanholo Paschoalini - 14558061
// Eduardo Poltroniere da Silva - 16862892
// Enzo Trulenque Evangelista - 15819219
// Pedro Hamamoto da Palma - 16818280

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da struct do grafo como uma matriz de adjacências
typedef struct graph
{
  int size;
  int **adj;
} GRAPH;

// Função auxiliar para alocação dinâmica de matriz de adjacências
int **alloc_matrix(int size)
{
  int **matrix = malloc(size * sizeof(int *));

  if (matrix == NULL)
    return NULL;

  for (int i = 0; i < size; i++)
  {
    matrix[i] = malloc(size * sizeof(int));

    // Libera toda a matriz caso haja erro na alocação de alguma linha
    if (matrix[i] == NULL)
    {
      for (int j = 0; j < i; j++)
        free(matrix[j]);

      free(matrix);
      return NULL;
    }
  }

  // Retorna um ponteiro para a matriz de adjacências
  return matrix;
}

// Função auxiliar para liberação de matriz de adjacências
void free_matrix(int **matrix, int size)
{
  if (matrix == NULL)
    return;

  for (int i = 0; i < size; i++)
    free(matrix[i]);

  free(matrix);
}

// Função para criar o grafo dada a quantidade de arrestas
GRAPH *MyGraph(int size)
{
  GRAPH *graph = malloc(sizeof(GRAPH));

  int **adj = alloc_matrix(size);

  // Encerra a função se houver problemas na alocação do grafo ou das colunas da
  // matriz de adjacência
  if (graph == NULL || adj == NULL)
  {
    free(graph);
    free(adj);

    return NULL;
  }

  // Pre-define todas as células da matriz como -1 (inicialmente não existem arestas)
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      adj[i][j] = -1;

  graph->size = size;
  graph->adj = adj;

  // Retorna um ponteiro para o grafo
  return graph;
}

// Função para deletar o grafo (liberar memória alocada)
void delete_graph(GRAPH **graph)
{
  if (graph != NULL && *graph != NULL)
  {
    free_matrix((*graph)->adj, (*graph)->size);

    free(*graph);

    *graph = NULL;
  }
}

// Função para adicionar uma aresta ao grafo informando os nós vizinhos e seu peso
void add_edge(GRAPH *graph, int node1, int node2, int weight)
{
  if (graph == NULL)
    return;

  graph->adj[node1 - 1][node2 - 1] = weight;
  graph->adj[node2 - 1][node1 - 1] = weight;
}

// Remove uma aresta entre dois nós se existir. Retorna 1 se removeu com sucesso, -1 caso contrário
int remove_edge(GRAPH *graph, int node1, int node2)
{
  if (graph == NULL)
    return -1;

  if (node1 < 1 || node1 > graph->size || node2 < 1 || node2 > graph->size)
    return -1;

  if (graph->adj[node1 - 1][node2 - 1] != -1)
  {
    graph->adj[node1 - 1][node2 - 1] = -1;
    graph->adj[node2 - 1][node1 - 1] = -1;
    return 1;
  }
  return -1;
}

// Verifica se existe uma aresta entre dois nós
bool exist_edge(GRAPH *graph, int node1, int node2)
{
  if (graph == NULL)
    return false;

  return graph->adj[node1 - 1][node2 - 1] != -1;
}

// Retorna array com os índices dos vizinhos de um nó (terminado com -1)
int *neighbors(GRAPH *graph, int node)
{
  if (graph == NULL)
    return NULL;

  int *neighbors_array = malloc((graph->size + 1) * sizeof(int));

  if (neighbors_array == NULL)
    return NULL;

  int neighbors_found = 0;
  for (int i = 0; i < graph->size; i++)
  {
    if (graph->adj[node - 1][i] != -1)
    {
      neighbors_array[neighbors_found] = i;
      neighbors_found++;
    }
  }
  neighbors_array[neighbors_found] = -1;
  return neighbors_array;
}

// Imprime os vértices e arestas do grafo no formato V = [...] E = [...]
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

  for (int j = 1; j < graph->size; j++)
  {
    for (int i = 0; i < j; i++)
    {
      if (graph->adj[i][j] != -1)
      {
        if (foundEdge)
          printf(", ");

        printf("(%d, %d)", i + 1, j + 1);
        foundEdge = true;
      }
    }
  }

  printf("]\n");
}

// Encontra o nó com maior quantidade de vizinhos
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
  return max_node + 1;
}

// Cria uma cópia da matriz de adjacência (para não modificar a original)
int **adjacency_matrix(GRAPH *graph)
{
  if (graph == NULL)
    return NULL;

  int **adj = alloc_matrix(graph->size);

  if (adj == NULL)
    return NULL;

  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++)
      adj[i][j] = graph->adj[i][j];

  return adj;
}

int main(void)
{
  int option;
  int N = 0, x, y, w;
  int res;
  bool print_status = false;

  GRAPH *G = NULL;

  // Loop principal: lê as opções até receber -1 para sair
  scanf("%d", &option);

  while (option != -1)
  {
    print_status = false;
    switch (option)
    {
    case 0:
      // Cria um novo grafo com N vértices
      scanf("%d", &N);
      G = MyGraph(N);
      print_status = true;
      break;
    case 1:
    {
      // Adiciona-se uma aresta com seu respectivo peso
      scanf("%d %d %d", &x, &y, &w);
      add_edge(G, x, y, w);
      print_status = true;
      break;
    }
    case 2:
      // Verifica se existe aresta entre dois nós
      scanf("%d %d", &x, &y);
      if (exist_edge(G, x, y))
        printf("1");
      else
        printf("0");
      break;
    case 3:
      // Imprime todos os vizinhos do nó lido
      scanf("%d", &x);
      int *v_vizinhos = neighbors(G, x);
      if (v_vizinhos != NULL)
      {
        int i = 0;
        while (v_vizinhos[i] != -1)
        {
          printf("%d ", v_vizinhos[i] + 1);
          i++;
        }
        printf("\n");
        free(v_vizinhos);
      }
      break;
    case 4:
      // Remove uma aresta. Caso não exista, retorna -1
      scanf("%d %d", &x, &y);
      res = remove_edge(G, x, y);
      if (res == -1)
        printf("-1");
      else
        print_status = true;
      break;
    case 5:
      // Exibe a matriz de adjacência
      printf("Adjacency Matrix:\n");
      int **adj_matrix = adjacency_matrix(G);
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          int curr_value = adj_matrix[i][j];
          if (curr_value == -1)
            curr_value++; // Caso a aresta não exista, incrementa 1 para, na impressão, apresentar 0 ao invés de -1
          if (j == N - 1)
            printf("%3d\n", curr_value);
          else
            printf("%3d ", curr_value);
        }
      }
      for (int i = 0; i < N; i++)
      {
        free(adj_matrix[i]);
      }
      free(adj_matrix);
      break;
    case 6:
      // Exibe o vértice com o maior número de vizinhos. Em caso de empate, imprime-se o primeiro encontrado (menor índice)
      printf("max vertex: %d\n", max_neighbors(G));
      break;
    default:
      printf("unrecognized option %d!\n", option);
    }
    scanf("%d", &option);
  }

  if (print_status)
    print_info(G);

  delete_graph(&G); // Desaloca toda memória dinâmica
  return 0;
}