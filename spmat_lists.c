/*
 * spmat_lists.c
 *
 *  Created on: 18 Jun 2020
 *      Author: computer
 */

#include "spmat_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
 *
 */
int add_row_linked_lists(spmat_lists *A, const double *row, int i){
	int j, as;
	A->rows[i] = allocate_row();
	if(A->rows[i] == NULL){
		free(A->rows[i]);
		return 0;
	}
	for(j = A->n - 1; j >= 0; j--){
		if(row[j] != 0.0){
			as = A->rows[i]->add(A->rows[i], row[j], j);
			if(!as) return as;
		}
	}
	return 1;
}

/*
 *
 */
void free_spmat_lists(spmat_lists *A){
	int i;
	for(i = 0; i < A->n; i++){
		A->rows[i]->free(A->rows[i]);
	}
	free(A->rows);
	free(A);
}



/*
 *
 */
void multiply_spmat_lists(const spmat_lists *A, const double *v, double *result){
	int i;
	linked_list *tmp;
	matrix_element *curr;
	for(i = 0; i < A->n; i++){
		result[i] = 0.0;
		tmp = A->rows[i]->lst;
		while(tmp != NULL){
			curr = (matrix_element*)tmp->value;
			result[i] += curr->value * v[curr->column] ;
		}
	}
}


/*
 *
 */
spmat_lists*  spmat_lists_allocate(int n){
	spmat_lists* res;
	res = (spmat_lists*)malloc(sizeof(spmat_lists));
	if(res == NULL){
		free(res);
		return NULL;
	}

	res->rows = (matrix_row**)calloc(n, sizeof(matrix_row*));
	if(res->rows == NULL){
		free(res->rows);
		free(res);
		return NULL;
	}

	res->n = n;
	res->add_row = add_row_linked_lists;
	res->free = free_spmat_lists;
	res->mult = multiply_spmat_lists;

	return res;
}
