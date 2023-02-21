#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int* data;
	int N;
	int n;
	int row_offset;
	int col_offset;
} matrix;

void matmul(int* A, int* B, int* C, int N);
void recmatmul(matrix A, matrix B, matrix C);
void strassens(matrix A, matrix B, matrix C);
void addmat(matrix a, matrix b, matrix c);
void submat(matrix a, matrix b, matrix c);
static int matidx(matrix M, int i, int j);
void initmat(matrix *M, int* data, int N, int n, int row_offset, int col_offset);
void partition(matrix M, matrix *M11, matrix *M12, matrix *M21, matrix *M22);
void printmat(matrix M);

