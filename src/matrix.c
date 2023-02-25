#include "matrix.h"

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

void recmatmul(matrix A, matrix B, matrix C) {
	if (C.n == 2) {
		C.data[matidx(C, 0, 0)] = A.data[matidx(A,0,0)]*B.data[matidx(B,0,0)] + A.data[matidx(A,0,1)]*B.data[matidx(B,1,0)];
		C.data[matidx(C, 0, 1)] = A.data[matidx(A,0,0)]*B.data[matidx(B,0,1)] + A.data[matidx(A,0,1)]*B.data[matidx(B,1,1)];
		C.data[matidx(C, 1, 0)] = A.data[matidx(A,1,0)]*B.data[matidx(B,0,0)] + A.data[matidx(A,1,1)]*B.data[matidx(B,1,0)];
		C.data[matidx(C, 1, 1)] = A.data[matidx(A,1,0)]*B.data[matidx(B,0,1)] + A.data[matidx(A,1,1)]*B.data[matidx(B,1,1)];
		return;
	}
	
	int m = C.n / 2;

	matrix As[2][2], Bs[2][2], Cs[2][2];
	partition(A, &As[0][0], &As[0][1], &As[1][0], &As[1][1]);
	partition(B, &Bs[0][0], &Bs[0][1], &Bs[1][0], &Bs[1][1]);
	partition(C, &Cs[0][0], &Cs[0][1], &Cs[1][0], &Cs[1][1]);
	
	matrix temp1, temp2;
	initmat(&temp1, (int*) calloc(C.n*C.n, sizeof(int)), C.n, m, 0, 0);
	initmat(&temp2, (int*) calloc(C.n*C.n, sizeof(int)), C.n, m, 0, 0);

	recmatmul(As[0][0], Bs[0][0], temp1);
	recmatmul(As[0][1], Bs[1][0], temp2);
	addmat(temp1, temp2, Cs[0][0]);
	
	recmatmul(As[0][0], Bs[0][1], temp1);
	recmatmul(As[0][1], Bs[1][1], temp2);
	addmat(temp1, temp2, Cs[0][1]);

	recmatmul(As[1][0], Bs[0][0], temp1);
	recmatmul(As[1][1], Bs[1][0], temp2);
	addmat(temp1, temp2, Cs[1][0]);

	recmatmul(As[1][0], Bs[0][1], temp1);
	recmatmul(As[1][1], Bs[1][1], temp2);
	addmat(temp1, temp2, Cs[1][1]);
}

void strassens(matrix A, matrix B, matrix C) {
	// base case (2 x 2 matrix)
	if (C.n == 2) {
		int M1 = (A.data[matidx(A,0,0)] + A.data[matidx(A,1,1)]) * (B.data[matidx(B,0,0)] + B.data[matidx(B,1,1)]);
		int M2 = (A.data[matidx(A,1,0)] + A.data[matidx(A,1,1)]) * B.data[matidx(B,0,0)];
		int M3 = A.data[matidx(A,0,0)] * (B.data[matidx(B,0,1)] - B.data[matidx(B,1,1)]);
		int M4 = A.data[matidx(A,1,1)] * (B.data[matidx(B,1,0)] - B.data[matidx(B,0,0)]);
		int M5 = (A.data[matidx(A,0,0)] + A.data[matidx(A,0,1)]) * B.data[matidx(B,1,1)];
		int M6 = (A.data[matidx(A,1,0)] - A.data[matidx(A,0,0)]) * (B.data[matidx(B,0,0)] + B.data[matidx(B,0,1)]);
		int M7 = (A.data[matidx(A,0,1)] - A.data[matidx(A,1,1)]) * (B.data[matidx(B,1,0)] + B.data[matidx(B,1,1)]);

		C.data[matidx(C, 0, 0)] = M1 + M4 - M5 + M7;
		C.data[matidx(C, 0, 1)] = M3 + M5;
		C.data[matidx(C, 1, 0)] = M2 + M4;
		C.data[matidx(C, 1, 1)] = M1 - M2 + M3 + M6;
		return;
	}
	
	// recursive case (n x n matrix)
	// partition the matrix into four equal blocks
	matrix A11,A12,A21,A22;
	matrix B11,B12,B21,B22;
	matrix C11,C12,C21,C22;
	partition(A, &A11, &A12, &A21, &A22);
	partition(B, &B11, &B12, &B21, &B22);
	partition(C, &C11, &C12, &C21, &C22);

	int n,m;
	n = C.n;
	m = n/2;

	// calculate our 7 multiplications
	matrix M1, M2, M3, M4, M5, M6, M7;
	initmat(&M1, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M2, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M3, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M4, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M5, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M6, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&M7, calloc(m*m, sizeof(int)), m, m, 0, 0);

	// temporary matrices for holding intermediate calculations
	matrix temp1, temp2;
	initmat(&temp1, calloc(m*m, sizeof(int)), m, m, 0, 0);
	initmat(&temp2, calloc(m*m, sizeof(int)), m, m, 0, 0);

	// M1 = (A11 + A22)(B11 + B22)
	addmat(A11, A22, temp1);
	addmat(B11, B22, temp2);
	strassens(temp1, temp2, M1);

	// M2 = (A21 + A22)B11
	addmat(A21, A22, temp1);
	strassens(temp1, B11, M2);

	// M3 = A11(B12 - B22)
	submat(B12, B22, temp1);
	strassens(A11, temp1, M3);

	// M4 = A22(B21 - B11)
	submat(B21, B11, temp1);
	strassens(A22, temp1, M4);

	// M5 = (A11 + A12)B22
	addmat(A11, A12, temp1);
	strassens(temp1, B22, M5);

	// M6 = (A21 - A11)(B11 + B12)
	submat(A21, A11, temp1);
	addmat(B11, B12, temp2);
	strassens(temp1, temp2, M6);

	// M7 = (A12 - A22)(B21 + B22)
	submat(A12, A22, temp1);
	addmat(B21, B22, temp2);
	strassens(temp1, temp2, M7);

	// C11 = M1 + M4 - M5 + M7
	addmat(M1, M4, temp1);
	submat(temp1, M5, temp2);
	addmat(temp2, M7, C11);

	// C12 = M3 + M5
	addmat(M3, M5, C12);

	// C21 = M2 + M4
	addmat(M2, M4, C21);

	// C22 = M1 - M2 + M3 + M6
	submat(M1, M2, temp1);
	addmat(temp1, M3, temp2);
	addmat(temp2, M6, C22);
}

static void addmat(matrix a, matrix b, matrix c) {
	int i,j;
	for (i = 0; i < c.n; i++) {
		for (j = 0; j < c.n; j++) {
			c.data[matidx(c, i, j)] = a.data[matidx(a, i, j)] + b.data[matidx(b,i,j)];
		}
	}
}

static void submat(matrix a, matrix b, matrix c) {
	int i,j;
	for (i = 0; i < c.n; i++) {
		for (j = 0; j < c.n; j++) {
			c.data[matidx(c, i, j)] = a.data[matidx(a, i, j)] - b.data[matidx(b,i,j)];
		}
	}
}

static int matidx(matrix M, int i, int j) {
	return (M.row_offset + i)*M.N + (M.col_offset + j);
}

void initmat(matrix* M, int* data, int N, int n, int row_offset, int col_offset) {
	M->data = data;
	M->N = N;
	M->n = n;
	M->row_offset = row_offset;
	M->col_offset = col_offset;
}

static void partition(matrix M, matrix *M11, matrix *M12, matrix *M21, matrix *M22) {
	int n = M.n / 2;
	initmat(M11, M.data, M.N, n, M.row_offset, M.col_offset);
	initmat(M12, M.data, M.N, n, M.row_offset, M.col_offset + n);
	initmat(M21, M.data, M.N, n, M.row_offset + n, M.col_offset);
	initmat(M22, M.data, M.N, n, M.row_offset + n, M.col_offset + n);
}

void printmat(matrix M) {
	int i, j;
	for (i = 0; i < M.n; i++) {
		for (j = 0; j < M.n; j++) {
			printf("%8d", M.data[matidx(M, i, j)]);
		}
		puts("");
	}
}

