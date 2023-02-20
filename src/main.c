#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	am_graph graph;
	am_graph_init(&graph, 10, 10);
	
	int i,j;
	for (i = 0; i < graph.n; i++) {
		for (j = 0; j < graph.n; j++) {
			printf("%d\t", graph.matrix[i*graph.n + j]);
		}
		puts("");
	}
	return 0;
}
