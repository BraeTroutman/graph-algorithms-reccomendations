#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int m;
	int n;
	int* matrix;
} am_graph;

void am_graph_init(am_graph *graph, int m, int n);
void am_graph_read(const char *filename, am_graph* graph);
void am_graph_print(am_graph graph);
void am_graph_2paths(am_graph graph, am_graph *result);

