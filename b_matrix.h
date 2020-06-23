/*
 * b_matrix.h
 *
 *  Created on: 23 Jun 2020
 *      Author: computer
 */

#ifndef B_MATRIX_H_
#define B_MATRIX_H_

#include "spmat_lists.h"

typedef struct _B_matrix {
	/*number of rows and columns in the matrix*/
	int n;

	/*vector of degrees of each vertex in the graph: k_i = sum(row[i])*/
	int *k;

	/*M = sum(k)*/
	int M;

	/*actual adjacency matrix of the graph*/
	spmat_lists *A;

	/*a value to be added to the diagonal of the matrix
	 *this is used for matrix shifting
	 */
	double lambda;

	/*after using this method: target = Bv */
	int (*multiply_vec)(struct _B_matrix* B, double* v, double* target);

	/*free all resources of this B matrix*/
	void (*free)(struct _B_matrix*);

} B_matrix;

/*allocates  a new B matrix and initializes it*/
B_matrix* allocate_B(int n, int *k, spmat_lists *A);

#endif /* B_MATRIX_H_ */
