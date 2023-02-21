#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "matrix.h"

int main(int argc, char* argv[]) {
	int N = 4;
	int i, j;

	int* smallnums = calloc(N*N, sizeof(int));
	int* smallidty = calloc(N*N, sizeof(int));

	matrix smallA, smallB;
	initmat(&smallA, smallnums, N, N, 0, 0);
	initmat(&smallB, smallidty, N, N, 0, 0);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			smallnums[i*N + j] = rand() % 5;
			smallidty[i*N + j] = (i == j) ? 1 : 0;
		}
	}

	matrix smallC;
	initmat(&smallC, calloc(N*N, sizeof(int)), N, N, 0, 0);

	puts("running unit test of small (4x4) matrix");
	strassens(smallA,smallB,smallC);

	for (i = 0; i < N*N; i++) assert(smallC.data[i] == smallA.data[i]);
	puts("assertion (C == A) passed");

	N = 1024;

	int *bignums = calloc(N*N, sizeof(int));
	int *bigidty = calloc(N*N, sizeof(int));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			bignums[i*N + j] = rand() % 5;
			bigidty[i*N + j] = (i == j) ? 1 : 0;
		}
	}

	matrix bigA, bigB, bigC;
	initmat(&bigA, bignums, N, N, 0, 0);
	initmat(&bigB, bigidty, N, N, 0, 0);
	initmat(&bigC, calloc(N*N, sizeof(int)), N, N, 0, 0);
	
	puts("running unit test of big (1024x1024) matrix");
	strassens(bigA, bigB, bigC);

	for (i = 0; i < N*N; i++) assert(bigC.data[i] == bigA.data[i]);
	puts("assertion (C == A) passed");
	
	free(smallnums);
	free(smallidty);
	free(bignums);
	free(bigidty);
	free(smallC.data);
	free(bigC.data);

	return 1;
}

