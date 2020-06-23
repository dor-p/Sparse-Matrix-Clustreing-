/*
 * norm_1.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#include "b_matrix.h"
#include "spmat_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
 * this is the function for the for_each
 *
int add_to_norm(matrix_element *elem, void *column_sums){
	double *double_sums = (double*)column_sums;
	double_sums[elem->column] += fabs(elem->value);
	return 1;
}*/

/*
 *calculates the norm_1 of B
 */
double norm_1(B_matrix* B){
	int i, j;
	double res, tmp;
	linked_list *curr;
	double *column_sums = (double*)calloc(B->n, sizeof(double));
	if(column_sums == NULL){
		free(column_sums);
		return -1.0;
	}
	/*note that at this point column_sums has all 0 because calloc makes it so*/
	for(i = 0; i < B->n; i++){
		curr = B->A->rows[i];
		/*this assumes that the matrix rows are sorted*/
		for(j = 0; j < B->n; j++){
			tmp = -((double)(B->k[i] * B->k[j]) / (double)B->M);
			if(i == j) tmp += B->lambda;
			if(curr != NULL && *((int*)(curr->value)) == j){
				tmp += 1;
				curr = curr->next;
			}
			column_sums[j] += fabs(tmp);
		}
	}
	res = 0.0;
	for(i = 0; i < B->n; i++){
		if(column_sums[i] > res) res = column_sums[i];
	}

	free(column_sums);
	return res;
}


