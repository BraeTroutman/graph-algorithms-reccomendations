#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	am_graph graph;

	am_graph_read("data/A16-edge.txt", &graph);

	am_graph_print(graph);

	return 0;
}
