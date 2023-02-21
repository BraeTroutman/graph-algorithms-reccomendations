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
am_graph* am_graph_two_paths(am_graph A, am_graph B);
void matmul(int* A, int* B, int* C, int N);
void strassens(int* A, int* B, int* C, int N);
void addmat(int* a, int* b, int* c, int n);
void submat(int* a, int* b, int* c, int n);

