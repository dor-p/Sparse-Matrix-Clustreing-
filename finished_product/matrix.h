
#ifndef MATRIX_H
#define MATRIX_H

#include "spmat_lists.h"
#include "linked_list.h"

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

  /* matrix of graph g*/
  spmat_lists *A;

  /*array holding the values of the diagonal of this matrix*/
  double *diagonal;

  /*for matrix shifting*/
  double lambda;

  double (*to_value)(struct SparseMatrix *mat, int row, int col, int con);

	/* pointer to the beginning of the array of linked-lists for rows */
	Node** rows; 
  /*todo delete rows, because we use matrix A */

	/* pointer to the beginning of the array of linked-lists for columns */
	Node** cols;

} SparseMatrix;

typedef struct _row_iterator{
  /*pointer to next node in adjacency list*/
  linked_list *curr;

  /*number of nodes in graph g*/
  int length;

  /*the row of this iterator*/
  int row;

  /*current column of iterator*/
  int col;

  /**/
  SparseMatrix *B;

  /*returns the value of the element in B and updates this iterator*/
  double (*get_next)(struct _row_iterator *I);

} Row_iterator;

/*return a new iterator over row */
Row_iterator* new_iterator(SparseMatrix *B, int row);

#endif

