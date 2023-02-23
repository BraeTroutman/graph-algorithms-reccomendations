#include <assert.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	puts("data/A16-edge.txt adjacency matrix representation");
	am_graph am;
	am_graph_read("data/A16-edge.txt", &am);
	am_graph_print(am);

	puts("\ndata/A16-edge.txt adjacency list represenstation");
	al_graph graph2;
	al_graph_read("data/A16-edge.txt", &graph2);
	al_graph_print(graph2);

	puts("\nadjacency matrix two-paths");
	am_graph paths;
	am_graph_2paths(am, &paths);
	am_graph_print(paths);

	puts("\nadjacency list two-paths");
	al_graph paths2;
	al_graph_2paths(graph2, &paths2);
	al_graph_print(paths2);

	return 0;
}
