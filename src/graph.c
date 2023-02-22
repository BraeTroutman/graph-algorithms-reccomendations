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
	printf("\n    +");
	for (i = 0; i < graph.n; i++) printf("--------");
	puts("+");
	for (i = 0; i < graph.n; i++) {
		printf("%4d|", i+1);
		for (j = 0; j < graph.n; j++) {
			printf("%8d", graph.matrix[i*graph.n + j]);
		}
		puts("|");
	}

	printf("    +");
	for (i = 0; i < graph.n; i++) printf("--------");
	puts("+");
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

void al_graph_init(al_graph *graph, int m, int n) {
	graph->m = m;
	graph->n = n;

	graph->nodes = calloc(n, sizeof(int));
	graph->num_edges = calloc(n, sizeof(int));
	graph->edges = calloc(m, sizeof(int));
}

void al_graph_read(const char *filename, al_graph *graph) {
	FILE* file = fopen(filename, "r");

	int m, n;
	fscanf(file, "m %d n %d", &m, &n);

	al_graph_init(graph, m, n);

	int i, src, dst, current_node = 0;
	for (i = 0; i < m; i++) {
		fscanf(file, "%d %d\n", &src, &dst);
		if (src > current_node) {
			current_node = src;
			graph->num_edges[(src-1)] = 1;
			graph->nodes[(src-1)] = i;
		} else {
			graph->num_edges[src-1]++;
		}
		graph->edges[i] = dst-1;
	}

	fclose(file);
}

void al_graph_print(al_graph graph) {
	int i, j;
	for (i = 0; i < graph.n; i++) {
		printf("%4i: ", i+1);
		for (j = 0; j < graph.num_edges[i]; j++) {
			printf("%5i", graph.edges[graph.nodes[i]+j]+1);
		}
		puts("");
	}
}

