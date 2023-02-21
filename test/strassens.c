#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "matrix.h"

int main(int argc, char* argv[]) {
	int N = atoi(argv[1]);
	int i, j;

	int* nums = calloc(N*N, sizeof(int));
	int* idty = calloc(N*N, sizeof(int));

	matrix A, B;
	initmat(&A, nums, N, N, 0, 0);
	initmat(&B, idty, N, N, 0, 0);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			nums[i*N + j] = rand() % 5;
			idty[i*N + j] = (i == j) ? 1 : 0;
		}
	}

	matrix C;
	initmat(&C, calloc(N*N, sizeof(int)), N, N, 0, 0);
	matrix checkC;
	initmat(&checkC, calloc(N*N, sizeof(int)), N, N, 0, 0);
	
	clock_t start = clock();
	recmatmul(A,B,checkC);
	float recmatmul_secs = (float)(clock() - start)/1000.0f;
	
	start = clock();
	strassens(A,B,C);
	float strassens_secs = (float)(clock() - start)/1000.0f;

	printf("%f/%f = %f\n", recmatmul_secs, strassens_secs, recmatmul_secs/strassens_secs);

	for (i = 0; i < N*N; i++) assert(C.data[i] == checkC.data[i]);

	return 1;
}

