#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int m;
	int n;
	int *matrix;
} am_graph;

typedef struct {
	int m;
	int n;
	int *edges;
	int *weights;
	int *nodes;
	int *num_edges;
} al_graph;

void am_graph_init(am_graph *graph, int m, int n);
void am_graph_read(const char *filename, am_graph *graph);
void am_graph_print(am_graph graph);
void am_graph_2paths(am_graph graph, am_graph *result);

void al_graph_init(al_graph *graph, int m, int n);
void al_graph_read(const char *filename, al_graph *graph);
void al_graph_print(al_graph graph);

#endif

