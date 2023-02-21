#include <stdio.h>
#include <time.h>

#include "matmul.h"

int main(int argc, char* argv[]) {
	int N = atoi(argv[1]);

	int* A = calloc(N*N, sizeof(int));
	int* B = calloc(N*N, sizeof(int));
	int* C = calloc(N*N, sizeof(int));
	
	float naive_time, strass_time;

	clock_t start, end;
	start = clock();

	matmul(A,B,C,N);

	end = clock();
	
	naive_time = (float)(end - start)/1000.0f;

	start = clock();

	strassens(A,B,C,N);

	end = clock();

	strass_time = (float)(end - start)/1000.0f;

	printf("%f/%f = %f\n", naive_time, strass_time, naive_time/strass_time);

	return 1;
}
	
