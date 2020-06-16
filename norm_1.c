/*
 * norm_1.c
 *
 *  Created on: 16 Jun 2020
 *      Author: computer
 */

#include "matrix_row.h"
#include "spmat_lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/*
 * this is the function for the for_each
 */
int add_to_norm(matrix_element *elem, double *column_sums){
	column_sums[elem->column] += abs(elem->value);
	return 1;
}

/*
 *
 */
double norm_1(spmat_lists* A){
	int i, as;
	double res;
	double *column_sums = (double*)calloc(A->n, sizeof(double));
	if(column_sums == NULL){
		free(column_sums);
		return -1.0;
	}
	/*note that at this point column_sums has all 0 because calloc makes it so*/
	for(i = 0; i < A->n; i++){
		as = (A->rows)[i]->for_each((A->rows)[i], add_to_norm, column_sums);
		if(!as){
			free(column_sums);
			return -1.0;
		}
	}
	res = 0.0;
	for(i = 0; i < A->n; i++){
		if(column_sums[i] > res) res = column_sums[i];
	}

	free(column_sums);
	return res;
}


