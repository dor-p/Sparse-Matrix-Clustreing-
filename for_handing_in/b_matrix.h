/*
 * b_matrix.h
 *
 *  Created on: 23 Jun 2020
 *      Author: computer
 */

#ifndef B_MATRIX_H_
#define B_MATRIX_H_

#include "spmat_lists.h"
#include "linked_list.h"

typedef struct _B_matrix {
	/*number of rows and columns in the matrix*/
	int n;

	/*vector of degrees of each vertex in the graph: k_i = deg(i)*/
	int *k;

	/*M = sum(k)*/
	int M;

	/*actual sparse adjacency matrix of the graph*/
	spmat_lists *A;

	/*a value to be added to the diagonal of the matrix
	 *this is used for matrix shifting
	 */
	double lambda;

	/*
	 * the values of the diagonal of this hatB
	 * hatB[i][i] = -(k[i]*k[i]/M) - sum(B[i][j] for j in g)
	 */
	double *diagonal;

	/*after using this method: target = Bv */
	int (*multiply_vec)(struct _B_matrix* B, double* v, double* target);

	/*free all resources of this B matrix*/
	void (*free)(struct _B_matrix*);

	/*compute actual value of hatB given: row and column such that
	 * if(val) there is a connection between row and col
	 * else: there isn't*/
	double (*to_value)(struct _B_matrix* B, int row, int col, int val);

} B_matrix;

/*allocates  a new B matrix and initializes it*/
B_matrix* allocate_B(spmat_lists *A, int *k, int M);

/*
 *returns the dot product of v and u
 */
double dot_product(double *v, double *u, int n);

typedef struct _row_iterator{
  /*pointer to next node in adjacency list*/
  linked_list *curr;

  /*number of nodes in graph g*/
  int length;

  /**/
  int row;

  /*current column of iterator*/
  int col;

  /**/
  B_matrix *B;

  /*returns the value of the element in B and updates this iterator*/
  double (*get_next)(struct _row_iterator *I);

} Row_iterator;

/*return a new iterator over row */
Row_iterator* new_iterator(B_matrix *B, int row);


#endif /* B_MATRIX_H_ */
