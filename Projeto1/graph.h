#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph GRAPH;

GRAPH *MyGraph(int size);

void delete_graph(GRAPH **graph);

void add_edge(GRAPH *graph, int node1, int node2, int weight);

int max_neighbors(GRAPH *graph);

void print_info(GRAPH *graph);

int **adjacency_matrix(GRAPH *graph);

#endif
