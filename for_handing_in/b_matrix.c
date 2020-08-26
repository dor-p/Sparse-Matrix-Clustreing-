/*
 * b_matrix.c
 *
 *  Created on: 26 Jul 2020
 *      Author: computer
 */

#include "b_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * writes B*v into target
 */
int multiply_vec_B(B_matrix* B, double* v, double* target){
	int i, j;
	Row_iterator* I;
	for(i = 0; i < B->n; i++){
		target[i] = 0.0;
		I = new_iterator(B, i);
		for(j = 0; j < B->n; j++){
			target[i] += I->get_next(I) * v[j];
		}
	}
	return 1;
}

/*
 * given to indecies of vetecies in the graph and whether
 * or not they are neighbors - returns hatB[row][col]
 */
double to_value(B_matrix* B, int row, int col, int val){
	if(row == col) return B->diagonal[row] + B->lambda;
	return (val ? 1.0 : 0.0) - (double)(B->k[row] * B->k[col]) / (double)B->M;
}


/*free all resources of B*/
void free_B(B_matrix* B){
	free(B->k);
	free(B->diagonal);
	B->A->free(B->A);
	free(B);
}


/* allocate ne B_matrix, given the adjecency matrix,
 * k - the degrees of all indecies and M the sum of degrees
 */
B_matrix* allocate_B(spmat_lists *A, int *k, int M){
	int i;
	B_matrix *res;
	res = (B_matrix*)malloc(sizeof(B_matrix));
	if(res == NULL || M == 0) return NULL;

	res->n = A->n;
	res->k = k;
	res->M = M;
	res->A = A;
	res->lambda = 0.0;
	res->to_value = to_value;

	res->diagonal = (double*)malloc(res->n * sizeof(double));
	if(res->diagonal == NULL){
		free(res);
		return NULL;
	}

	/*
	 * Bg[i][i] = B[i][i] - sum(B[i][j] for j in g) =
	 * = - sum(B[i][j] for j in g if j != i)
	 */
	for(i = 0; i < res->n; i++){
		res->diagonal[i] = -(double)(k[i] * k[i]) / (double)M;
	}

	res->free = free_B;
	res->multiply_vec = multiply_vec_B;

	return res;
}


/* return the dot product between v and u,
 * two vectors of length n
 */
double dot_product(double *v, double *u, int n){
	int i;
	double res = 0.0;
	for(i = 0; i < n; i++){
		res += v[i] * u[i];
	}
	return res;
}


/*
 * An iterator for iterating over a row of B_matrix
 */
 /*advances I by one and returns the next value in the iteration*/
double get_next_b(Row_iterator *I){
  int con;
  double res;
  con = (I->curr != NULL) && I->col == *(int*)I->curr->value;
  res = I->B->to_value(I->B, I->row, I->col, con);
  I->col = I->col + 1;
  if(con) I->curr = I->curr->next;
  if(I->col >= I->length){
    free(I);
  }
  return res;
}

/*
 * returns a new iterator for argument row
 * note, that appone returning the last value,
 * the iterator will free its own resources
 */
Row_iterator* new_iterator(B_matrix *B, int row){
  Row_iterator* res;
  res = (Row_iterator*)malloc(sizeof(Row_iterator));
  if(res == NULL) return NULL;

  res->curr = B->A->rows[row];
  res->length = B->n;
  res->row = row;
  res->col = 0;
  res->B = B;
  res->get_next = get_next_b;

  return res;

}
