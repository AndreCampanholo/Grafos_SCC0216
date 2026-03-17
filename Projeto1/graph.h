#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph GRAPH;

GRAPH *MyGraph(int n);
void add_edge(GRAPH *G, int source_node, int dest_node, int edge_weight);
int existe_edge(GRAPH *G, int source_node, int dest_node);
int *neighbors(GRAPH *G, int node);
void remove_edge(GRAPH *G, int source_node, int dest_node);
void print_info(GRAPH *G);
void delete_graph(GRAPH **G);
int most_neighbors(GRAPH *G);
int **adjacency_matrix(GRAPH *G);