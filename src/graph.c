#include "graph.h"

void am_graph_init(am_graph* graph, int m, int n) {
	graph->m = m;
	graph->n = n;
	graph->matrix = calloc(n*n, sizeof(int));
}
