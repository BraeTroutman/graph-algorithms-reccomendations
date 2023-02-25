#include <assert.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	puts("data/A16-edge.txt adjacency matrix representation");
	am_graph am;
	am_graph_read("data/A16-edge.txt", &am);
	am_graph_print(am);

	puts("\ndata/A16-edge.txt adjacency list represenstation");
	al_graph al;
	al_graph_read("data/A16-edge.txt", &al);
	al_graph_print(al);

	puts("\nadjacency matrix two-paths");
	am_graph am_paths;
	am_graph_2paths(am, &am_paths);
	am_graph_print(am_paths);
	
	int i, *reccs = calloc(am_paths.n, sizeof(int));
	am_graph_heaviest_edges(am_paths, reccs, 1);
	puts("\nadjacency matrix reccomendations (heaviest edges per node)");
	for (i = 0; i < am_paths.n; i++) printf("node %i's heaviest node is %i\n", i+1, reccs[i]+1);

	puts("\nadjacency list two-paths");
	al_graph al_paths;
	al_graph_2paths(al, &al_paths);
	al_graph_print(al_paths);
	al_graph_heaviest_edges(al_paths, reccs, 1);
	puts("\nadjacency list reccomendations (heaviest edges per node");
	for (i = 0; i < am_paths.n; i++) printf("node %i's heaviest node is %i\n", i+1, reccs[i]+1);

	return 0;
}

