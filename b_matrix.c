/*
 * b_matrix.c
 *
 *  Created on: 26 Jul 2020
 *      Author: computer
 */

#include "b_matrix.h"
#include <stdio.h>


int multiply_vec_B(B_matrix* B, double* v, double* target){
	int i, j, con;
	linked_list* curr;
	for(i = 0; i < B->n; i++){
		target[i] = 0.0;
		curr = B->A->rows[i];
		if(curr == NULL) continue;
		for(j = 0; j < B->n; j++){
			con = (j == *(int*)curr->value);
			target[i] += to_value(B, i, j, con);
			if(con) curr = curr->next;
		}
	}
	return 1;
}

double to_value(B_matrix* B, int row, int col, int val){
	if(row == col) return B->diagonal[row] + B->lambda;
	return (val ? 1 : 0) - (double)(B->k[row] * B->k[col]) / (double)B->M;
}



void free_B(B_matrix* B){
	free(B->k);
	free(B->diagonal);
	B->A->free(B->A);
}



B_matrix* allocate_B(spmat_lists *A, int *k, int M){
	int i;
	linked_list* curr;
	B_matrix *res;
	res = (B_matrix*)malloc(sizeof(B_matrix));
	if(res == NULL) return NULL;

	res->n = A->n;
	res->k = k;
	res->M = M;
	res->lambda = 0.0;

	res->diagonal = (double*)malloc(res->n * sizeof(double));
	if(res->diagonal == NULL){
		free(res);
		return NULL;
	}

	for(i = 0; i < res->n; i++){
		res->diagonal[i] = -(double)(res->k[i] * res->k[i]) / (double)res->M;
		curr = A->rows[i];
		if(curr == NULL) continue;
		while(curr != NULL){
			res->diagonal[i] -= res->to_value(res, i, *(int*)curr->value, 1);
			curr = curr->next;
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
