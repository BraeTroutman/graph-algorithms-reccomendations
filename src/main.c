#include <assert.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	am_graph graph;

	am_graph_read("data/A4-edge.txt", &graph);

	am_graph_print(graph);
	
	am_graph paths;
	am_graph_2paths(graph, &paths);
	am_graph_print(paths);

	return 0;
}
