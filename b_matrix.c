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


int multiply_vec_B(B_matrix* B, double* v, double* target){
	int i, j, con;
	linked_list* curr;
	for(i = 0; i < B->n; i++){
		target[i] = 0.0;
		curr = B->A->rows[i];
		for(j = 0; j < B->n; j++){
			con = (curr != NULL && j == *(int*)curr->value);
			target[i] += B->to_value(B, i, j, con) * v[j];
			if(con) curr = curr->next;
		}
	}
	return 1;
}

double to_value(B_matrix* B, int row, int col, int val){
	if(row == col) return B->diagonal[row] + B->lambda;
	return (double)(val ? 1 : 0) - (double)(B->k[row] * B->k[col]) / (double)B->M;
}



void free_B(B_matrix* B){
	free(B->k);
	free(B->diagonal);
	B->A->free(B->A);
	free(B);
}



B_matrix* allocate_B(spmat_lists *A, int *k, int M){
	int i, j, con;
	linked_list* curr;
	B_matrix *res;
	res = (B_matrix*)malloc(sizeof(B_matrix));
	if(res == NULL) return NULL;

	res->n = A->n;
	res->k = k;
	res->M = M;
	res->A = A;
	res->lambda = 0.0;

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
		res->diagonal[i] = 0.0;
		curr = A->rows[i];
		for(j = 0; j < res->n; j++){
			if(i == j) continue;
			con = (curr!= NULL && *(int*)(curr->value) == j);
			res->diagonal[i] -= to_value(res, i, j, con);
			if(con) curr = curr->next;
		}
	}

	res->free = free_B;
	res->multiply_vec = multiply_vec_B;
	res->to_value = to_value;

	return res;
}



double dot_product(double *v, double *u, int n){
	int i;
	double res = 0.0;
	for(i = 0; i < n; i++){
		res += v[i] * u[i];
	}
	return res;
}

double get_next_b(Row_iterator *I){
  int con;
  double res;
  con = (I->curr != NULL) && I->col == *(int*)I->curr->value;
  res = I->B->to_value(I->B, I->row, I->col, con);
  I->col = I->col + 1;
  if(I->col >= I->length){
    free(I);
  }
  if(con) I->curr = I->curr->next;
  return res;
}

Row_iterator* new_iterator(B_matrix *B, int row){
  Row_iterator* res;
  res = (Row_iterator*)malloc(sizeof(Row_iterator));
  if(res == NULL) return NULL;

  res->curr = B->A->rows[i];
  res->length = B->n;
  res->row = row;
  res->col = 0;
  res->B = B;
  res->get_next = get_next_b;

  return res;

}