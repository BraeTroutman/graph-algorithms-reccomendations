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
			if (graph.matrix[i*graph.n + j] > 0) {
				printf("\033[1m\033[32m%8d\033[0m", graph.matrix[i*graph.n + j]);
			} else {
				printf("%8d", graph.matrix[i*graph.n + j]);
			}
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

void am_graph_heaviest_edges(am_graph graph, int *heaviest_edges, int exclude_self) {
	int i, j;
	int max_edge, max_weight;
	int src_edges_idx;

	for (i = 0; i < graph.n; i++) {
		max_edge = -1; 
		max_weight = 0;
		for (j = 0; j < graph.n; j++) {
			if (exclude_self && i == j) continue;
			// check if weight at this edge is bigger than current max
			if (graph.matrix[i*graph.n + j] > max_weight) {
				max_weight = graph.matrix[i*graph.n + j];
				max_edge = j;
			}
		}
		heaviest_edges[i] = max_edge;
	}
}

void al_graph_init(al_graph *graph, int m, int n) {
	graph->m = m;
	graph->n = n;

	graph->nodes = calloc(n, sizeof(int));
	graph->num_edges = calloc(n, sizeof(int));
	graph->edges = calloc(m, sizeof(int));
	graph->weights = calloc(m, sizeof(int));
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
		graph->weights[i] = 1;
	}

	fclose(file);
}

void al_graph_print(al_graph graph) {
	int i, j;
	puts("node: (edge,weight)");
	for (i = 0; i < graph.n; i++) {
		printf("%4i: ", i+1);
		for (j = 0; j < graph.num_edges[i]; j++) {
			printf("(%i,%i)", graph.edges[graph.nodes[i]+j]+1, graph.weights[graph.nodes[i]+j]);
		}
		puts("");
	}
}

void al_graph_2paths(al_graph graph, al_graph *result) {
	// pass 1 -> count the number of edges (number of total two-paths
	int i, j, k, m = 0;
	int src, nbr, dst;

	int visited[graph.n];
	for (i = 0; i < graph.n; i++) visited[i] = 0;

	// for every node in our graph
	for (src = 0; src < graph.n; src++) {
		// for every neighbor of the current source node
		for (j = 0; j < graph.num_edges[src]; j++) {
			nbr = graph.edges[graph.nodes[src]+j];
			// for every neighbor of the current neighbor node,
			//   i.e. every node exactly two hops away from src
			for (k = 0; k < graph.num_edges[nbr]; k++) {
				dst = graph.edges[graph.nodes[nbr]+k];
				// if we haven't visited this node from the src yet
				//   then we can add to the total number of edges
				if (!visited[dst]) {
					m++;
					visited[dst] = 1;
				}
			}
		}
		
		// reset visited to all zeroes, only checking the values we know we updated
		for (j = 0; j < graph.num_edges[src]; j++) {
			nbr = graph.edges[graph.nodes[src]+j];
			for (k = 0; k < graph.num_edges[nbr]; k++) {
				dst = graph.edges[graph.nodes[nbr]+k];
				visited[dst] = 0;
			}
		}
	}

	al_graph_init(result, m, graph.n);

	// pass 2 -> fill the adjacency list with edges
	
	int edgeidx = 0;
	for (src = 0; src < graph.n; src++) {
		for (i = 0; i < graph.n; i++) visited[i] = 0;
		// for every neighbor of the current source node
		for (j = 0; j < graph.num_edges[src]; j++) {
			nbr = graph.edges[graph.nodes[src]+j];
			// for every neighbor of the current neighbor node,
			//   i.e. every node exactly two hops away from src
			for (k = 0; k < graph.num_edges[nbr]; k++) {
				dst = graph.edges[graph.nodes[nbr]+k];
					
				visited[dst]++;	
			}
		}
		// fill our array with our calculated edge/weight pairs
		result->nodes[src] = edgeidx;
		for (j = 0; j < graph.num_edges[src]; j++) {
			nbr = graph.edges[graph.nodes[src]+j];
			for (k = 0; k < graph.num_edges[nbr]; k++) {
				dst = graph.edges[graph.nodes[nbr]+k];
				if (visited[dst]) {
					result->edges[edgeidx] = dst;
					result->weights[edgeidx] = visited[dst];
					visited[dst] = 0;
					result->num_edges[src]++;
					edgeidx++;
				}
			}
		}
	}
}

void al_graph_heaviest_edges(al_graph graph, int *heaviest_edges, int exclude_self) {
	int i, j;
	int max_edge, max_weight;
	int src_edges_idx;

	for (i = 0; i < graph.n; i++) {
		src_edges_idx = graph.nodes[i];
		max_edge = -1; 
		max_weight = 0;
		for (j = 0; j < graph.num_edges[i]; j++) {
			if (exclude_self && i == j) continue;
			// check if weight at this edge is bigger than current max
			if (graph.weights[src_edges_idx+j] > max_weight) {
				max_weight = graph.weights[src_edges_idx+j];
				max_edge = graph.edges[src_edges_idx+j];
			}
		}
		heaviest_edges[i] = max_edge;
	}
}

int al_graph_edge_exists(al_graph graph, int u, int v) {
	int node = graph.nodes[u];

	int i;
	for (i = 0; i < graph.num_edges[u]; i++) {
		if (graph.edges[u + i] == v) return 1;
	}

	return 0;
}

