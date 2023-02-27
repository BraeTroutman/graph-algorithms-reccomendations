#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

// matrix structure for constant time in-place partitioning
//   tracks the top left-hand corner of the matrix in the 
//   row-major data and fashions calculations around that
typedef struct {
	int* data;
	int N;
	int n;
	int row_offset;
	int col_offset;
} matrix;

// classical matrix multiplication
void matmul(int* A, int* B, int* C, int N);
// classical recursive matrix multiplication
void recmatmul(matrix A, matrix B, matrix C);
// strassen's recursive matrix multiplication
void strassens(matrix A, matrix B, matrix C);
// add matrices A and B and store in C
static void addmat(matrix a, matrix b, matrix c);
// subtract matrices A and B and store in C
static void submat(matrix a, matrix b, matrix c);
// translate indices relative to the partitioned matrix
// into indices in the underlying global matrix data
static int matidx(matrix M, int i, int j);
// create matrix
void initmat(matrix *M, int* data, int N, int n, int row_offset, int col_offset);
// partition matrix into four sub-blocks in constant time
static void partition(matrix M, matrix *M11, matrix *M12, matrix *M21, matrix *M22);
// print a matrix
void printmat(matrix M);

#endif

