#include <assert.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	am_graph am;
	am_graph_read("data/A4-edge.txt", &am);
	am_graph_print(am);

	puts("\tALL TWO-PATHS");
	am_graph paths;
	am_graph_2paths(am, &paths);
	am_graph_print(paths);
	
	puts("");
	al_graph graph2;
	al_graph_read("data/A4-edge.txt", &graph2);
	al_graph_print(graph2);
	al_graph paths2;
	al_graph_2paths(graph2, &paths2);
	return 0;
}
