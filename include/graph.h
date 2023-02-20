#include <stdlib.h>

typedef struct {
	int m;
	int n;
	int* matrix;
} am_graph;

void am_graph_init(am_graph *graph, int m, int n);

