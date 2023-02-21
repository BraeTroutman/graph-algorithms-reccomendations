#include "graph.h"

void am_graph_init(am_graph* graph, int m, int n) {
	graph->m = m;
	graph->n = n;
	graph->matrix = calloc(n*n, sizeof(int));
}

void am_graph_read(const char *filename, am_graph* graph) {
	FILE* file = fopen(filename, "r");
	
	int m,n;
	fscanf(file, "m %d n %d", &m, &n);
	
	am_graph_init(graph, m, n);	

	int idx,i,j;
	for (idx = 0; idx < m; idx++) {
		fscanf(file, "%d %d\n", &i, &j);
		graph->matrix[(i-1)*n + (j-1)] = 1;
	}

	fclose(file);
}

void am_graph_print(am_graph graph) {
	int i,j;
	printf("     ");
	for (i = 1; i <= graph.n; i++) printf("%8d", i);
	puts("");
	for (i = 0; i < graph.n; i++) {
		printf("%4d|", i+1);
		for (j = 0; j < graph.n; j++) {
			printf("%8d", graph.matrix[i*graph.n + j]);
		}
		puts("");
	}
}

am_graph* am_graph_two_paths(am_graph A, am_graph B) {
	am_graph* C = calloc(1, sizeof(am_graph));
	am_graph_init(C, A.m, A.n);

	strassens(A.matrix, B.matrix, C->matrix, C->n);
	
	return C;
}

void matmul(int* A, int* B, int* C, int N) {
	int i,j,k;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i*N + j] = 0;
			for (k = 0; k < N; k++) {
				C[i*N + j] += A[i*N + k] * B[k*N + j];
			}
		}
	}
}

void strassens(int* A, int* B, int* C, int N) {
	if (N == 2) {
		int M1 = (A[0] + A[3]) * (B[0] + B[3]);
		int M2 = (A[2] + A[3]) * B[0];
		int M3 = A[0] * (B[1] - B[3]);
		int M4 = A[3] * (B[2] - B[0]);
		int M5 = (A[0] + A[1]) * B[3];
		int M6 = (A[2] - A[0]) * (B[0] + B[1]);
		int M7 = (A[1] - A[3]) * (B[2] + B[3]);

		C[0] = M1 + M4 - M5 + M7;
		C[1] = M3 + M5;
		C[2] = M2 + M4;
		C[3] = M1 - M2 + M3 + M6;

		return;
	}

	int i,j,m = N / 2;

	int *A11 = calloc(m*m, sizeof(int));
	int *A12 = calloc(m*m, sizeof(int));
	int *A21 = calloc(m*m, sizeof(int));
	int *A22 = calloc(m*m, sizeof(int));
	
	int *B11 = calloc(m*m, sizeof(int));
	int *B12 = calloc(m*m, sizeof(int));
	int *B21 = calloc(m*m, sizeof(int));
	int *B22 = calloc(m*m, sizeof(int));

	int *C11 = calloc(m*m, sizeof(int));
	int *C12 = calloc(m*m, sizeof(int));
	int *C21 = calloc(m*m, sizeof(int));
	int *C22 = calloc(m*m, sizeof(int));

	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			A11[i*m + j] = A[i*N + j];
			A12[i*m + j] = A[i*N + j + m];
			A21[i*m + j] = A[(m+i)*N + j];
			A22[i*m + j] = A[(m+i)*N + j + m];

			B11[i*m + j] = B[i*N + j];
			B12[i*m + j] = B[i*N + j + m];
			B21[i*m + j] = B[(m+i)*N + j];
			B22[i*m + j] = B[(m+i)*N + j + m];
		}
	}

	int* temp1 = calloc(m*m, sizeof(int));
	int* temp2 = calloc(m*m, sizeof(int));
	
	// M1 = (A11 + A22)(B11 + B22)
	int* M1 = calloc(m*m, sizeof(int));
	addmat(A11,A22,temp1,m);
	addmat(B11,B22,temp2,m);
	strassens(temp1,temp2,M1,m);

	// M2 = (A21 + A22) * B11
	int* M2 = calloc(m*m, sizeof(int));
	addmat(A21, A22, temp1, m);
	strassens(temp1,B11,M2, m);

	// M3 = A11 * (B12 - B22)
	int* M3 = calloc(m*m, sizeof(int));
	submat(B12, B22, temp1, m);
	strassens(A11, temp1, M3, m);

	// M4 = A22 * (B21 - B11)
	int* M4 = calloc(m*m, sizeof(int));
	submat(B21, B11, temp1, m);
	strassens(A22, temp1, M4, m);

	// M5 = (A11 + A12) * B22
	int* M5 = calloc(m*m, sizeof(int));
	addmat(A11, A12, temp1, m);
	strassens(temp1, B22, M5, m);

	// M6 = (A21 - A11)(B11 + B12)
	int* M6 = calloc(m*m, sizeof(int));
	submat(A21, A11, temp1, m);
	addmat(B11, B12, temp2, m);
	strassens(temp1, temp2, M6, m);

	// M7 = (A12 - A22)(B21 + B22)
	int* M7 = calloc(m*m, sizeof(int));
	submat(A12, A22, temp1, m);
	addmat(B21, B22, temp2, m);
	strassens(temp1, temp2, M7, m);

	addmat(M1, M4, temp1, m);
	submat(temp1, M5, temp2, m);
	addmat(temp2, M7, C11, m);

	addmat(M3, M5, C12, m);

	addmat(M2, M4, C21, m);

	submat(M1, M2, temp1, m);
	addmat(M3, M6, temp2, m);
	addmat(temp1, temp2, C22, m);
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			C[i*N + j]         = C11[i*m + j];
			C[i*N + j + m]     = C12[i*m + j];
			C[(i+m)*N + j]     = C21[i*m + j];
			C[(i+m)*N + j + m] = C22[i*m + j];
		}
	}
}

void addmat(int* a, int* b, int* c, int n) {
	int i;
	for (i = 0; i < n*n; i++) {
		c[i] = a[i] + b[i];
	}
}

void submat(int* a, int* b, int* c, int n) {
	int i;
	for (i = 0; i < n*n; i++) {
		c[i] = a[i] - b[i];
	}
}

