#include <assert.h>
#include <time.h>

#include "graph.h"
#include "words.h"

void calculate_reccomendations_exclusive(al_graph paths, al_graph original) {
	FILE *out = fopen("data/out/rec1024.txt", "w");
	
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

void calculate_reccomendations_inclusive(al_graph paths) {
	FILE *out = fopen("data/out/inclusive/rec1024.txt", "w");
	
	int *reccs = calloc(paths.n, sizeof(int));
	al_graph_heaviest_edges(paths, reccs, 0);

	int i; 
	for (i = 0; i < paths.n; i++) {
		fprintf(out, "%d\n", reccs[i]+1);
	}

	fclose(out);
}

int main(int argc, char* argv[]) {
	clock_t start, mat_time, list_time;

	puts("reading to amatrix");
	am_graph am;
	am_graph_read("data/A1024-edge.txt", &am);

	puts("reading to alist");
	al_graph al;
	al_graph_read("data/A1024-edge.txt", &al);
	//al_graph_print(al);
	
	puts("\ncalculating 2paths amatrix");
	start = clock();
	puts("\nadjacency matrix two-paths");
	am_graph am_paths;
	am_graph_2paths(am, &am_paths);
	mat_time = clock() - start;
	printf("took %f seconds\n", ((float) mat_time)/CLOCKS_PER_SEC);

	puts("\ncalculating 2paths alist");
	start = clock();
	al_graph al_paths;
	al_graph_2paths(al, &al_paths);
	list_time = clock() - start;
	printf("took %f seconds\n", ((float) list_time)/CLOCKS_PER_SEC);

	printf("The adjacency list algorithm was %f times faster\n", 
			((float)mat_time / CLOCKS_PER_SEC) / ((float) list_time / CLOCKS_PER_SEC));	
	
	calculate_reccomendations_exclusive(al_paths, al);

	return 0;
}
