#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

// adjacency matrix representation of a graph
typedef struct {
	int m;			// number of edges
	int n;			// number of nodes
	int *matrix;	// edges
} am_graph;

typedef struct {
	int m;			// number of edges
	int n;			// number of nodes
	int *edges;		// array storing all edge destinations
	int *weights;	// array storing weights for each edge
	int *nodes;		// array of indices into edge/weight arrays
	int *num_edges;	// number of edges from each node
} al_graph;

// create am_graph
void am_graph_init(am_graph *graph, int m, int n);
// read am_graph from filename
void am_graph_read(const char *filename, am_graph *graph);
// print am_graph as a matrix
void am_graph_print(am_graph graph);
// use matrix multiplication to find the weighted graph of
// numbers of two paths from each node to every other
void am_graph_2paths(am_graph graph, am_graph *result);
// find the heaviest edge leading out of each node
void am_graph_heaviest_edges(am_graph graph, int *heaviest_edges, int exclude_self);

// create al_graph
void al_graph_init(al_graph *graph, int m, int n);
// read al_graph from filename
void al_graph_read(const char *filename, al_graph *graph);
// print al_graph as adjacency list
void al_graph_print(al_graph graph);
// calculate number of 2paths from each node to every other
void al_graph_2paths(al_graph graph, al_graph *result);
// find the heaviest edge from each node
void al_graph_heaviest_edges(al_graph graph, int *heaviest_edges, int exclude_self);
// return 1 if edge (u,v) is in graph, 0 otherwise
int  al_graph_edge_exists(al_graph graph, int u, int v);

#endif

