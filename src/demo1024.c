#include <assert.h>
#include <time.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	float start, mat_time, list_time;

	puts("reading to amatrix");
	am_graph am;
	am_graph_read("data/A1024-edge.txt", &am);

	puts("reading to alist");
	al_graph al;
	al_graph_read("data/A1024-edge.txt", &al);
	al_graph_print(al);
	
	puts("\ncalculating 2paths amatrix");
	start = (float) clock();
	puts("\nadjacency matrix two-paths");
	am_graph am_paths;
	am_graph_2paths(am, &am_paths);
	mat_time = ((float) clock() - start)/1000.0f;
	printf("took %f seconds\n", mat_time);

	puts("\ncalculating 2paths alist");
	start = (float) clock();
	al_graph al_paths;
	al_graph_2paths(al, &al_paths);
	list_time = ((float) clock() - start)/1000.0f;
	printf("took %f seconds\n", list_time);

	printf("The adjacency list algorithm was %f times faster", mat_time / list_time);	

	return 0;
}
