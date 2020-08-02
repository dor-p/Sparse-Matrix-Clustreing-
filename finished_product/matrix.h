
#ifndef MATRIX_H
#define MATRIX_H

/* linked-list node */
typedef struct Node
{
	/* value in this node */
	double value;

	/* row index of this node */
	int row;

	/* column index of this node */
	int column;

	/* pointer to the next non-zero element in the same row */
	struct Node* right;

	/* pointer to the next non-zero element in the same column */
	struct Node* down;

} Node;

typedef struct SparseMatrix
{
	/* Matrix size (n*n) */
	int n;

	/* array of size n which contains the degrees of vertices in the graph */
	int* k;

	/* sum of all of the degrees of vertices in the graph */
	int M;

	/* pointer to the beginning of the array of linked-lists for rows */
	Node** rows;

	/* pointer to the beginning of the array of linked-lists for columns */
	Node** cols;

} SparseMatrix;

#endif

