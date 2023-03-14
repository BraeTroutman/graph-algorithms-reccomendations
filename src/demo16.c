#include <assert.h>
#include <time.h>

#include "graph.h"

void calculate_reccomendations_exclusive(al_graph paths, al_graph original) {
	FILE *out = fopen("data/out/rec16.txt", "w");
	
	int i, j;

	for (i = 0; i < paths.n; i++) {
		int max_weight = 0;
		int max_edge = -1;
		int src = paths.nodes[i];

		for (j = 0; j < paths.num_edges[i]; j++) {
			int dst = paths.edges[src+j];
			if (al_graph_edge_exists(original, i, dst) || i == dst) continue;
			if (paths.weights[src+j] > max_weight) {
				max_weight = paths.weights[src+j];
				max_edge = dst;
			}
		}
		fprintf(out, "%d\n", max_edge+1);	
	}

	fclose(out);
}


int main(int argc, char* argv[]) {
	clock_t start, lst_time, mat_time;
	//puts("data/A16-edge.txt adjacency matrix representation");
	am_graph am;
	am_graph_read("data/A16-edge.txt", &am);
	//am_graph_print(am);

	//puts("\ndata/A16-edge.txt adjacency list represenstation");
	al_graph al;
	al_graph_read("data/A16-edge.txt", &al);
	//al_graph_print(al);
	
	start = clock();
	//puts("\nadjacency matrix two-paths");
	am_graph am_paths;
	am_graph_2paths(am, &am_paths);
	mat_time = clock() - start;
	printf("adjacency matrix 2 paths took %f seconds to calculate\n", 
			(float) mat_time / CLOCKS_PER_SEC);

	start = clock();
	//puts("\nadjacency list two-paths");
	al_graph al_paths;
	al_graph_2paths(al, &al_paths);
	lst_time = clock() - start;
	printf("adjacency list 2 paths took %f seconds to calculate\n", 
			(float) lst_time / CLOCKS_PER_SEC);
	printf("adjacency list was %.2fx faster\n", (float) mat_time / (float) lst_time);
	
	al_graph_print(al_paths);
	am_graph_print(am_paths);

	calculate_reccomendations_exclusive(al_paths, al);

	return 0;
}

