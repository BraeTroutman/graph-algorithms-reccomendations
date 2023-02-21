#include "graph.h"
#include "matrix.h"

void am_graph_init(am_graph* graph, int m, int n) {
	graph->m = m;
	graph->n = n;
	graph->matrix = calloc(n*n, sizeof(int));
}

void am_graph_read(const char *filename, am_graph* graph) {
	FILE* file = fopen(filename, "r");
	
	int m,n;
	fscanf(file, "m %d n %d", &m, &n);
	
	am_graph_init(graph, m, n);	

	int idx,i,j;
	for (idx = 0; idx < m; idx++) {
		fscanf(file, "%d %d\n", &i, &j);
		graph->matrix[(i-1)*n + (j-1)] = 1;
	}

	fclose(file);
}

void am_graph_print(am_graph graph) {
	int i,j;
	printf("     ");
	for (i = 1; i <= graph.n; i++) printf("%8d", i);
	puts("");
	for (i = 0; i < graph.n; i++) {
		printf("%4d|", i+1);
		for (j = 0; j < graph.n; j++) {
			printf("%8d", graph.matrix[i*graph.n + j]);
		}
		puts("");
	}
}

void am_graph_2paths(am_graph graph, am_graph *result) {
	matrix A, C;
	initmat(&A, graph.matrix, graph.n, graph.n, 0, 0);
	initmat(&C, calloc(graph.n*graph.n, sizeof(int)), graph.n, graph.n, 0, 0);
	
	result->n = graph.n;
	result->m = graph.m;
	strassens(A, A, C);

	result->matrix = C.data;
}

