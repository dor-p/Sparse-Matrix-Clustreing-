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
 *calculates the norm_1 of B
 */
double norm_1(B_matrix* B){
	int i, j;
	double res;
	Row_iterator *I;
	double *column_sums = (double*)calloc(B->n, sizeof(double));
	if(column_sums == NULL){
		free(column_sums);
		return 0;
	}
	/*note that at this point column_sums has all 0 because calloc makes it so*/
	for(i = 0; i < B->n; i++){
		I = new_iterator(B, i);
		/*this assumes that the matrix rows are sorted*/
		for(j = 0; j < B->n; j++){
			column_sums[j] += fabs(I->get_next(I));
		}
	}
	res = 0.0;
	for(i = 0; i < B->n; i++){
		if(column_sums[i] > res) res = column_sums[i];
	}

	free(column_sums);
	return res;
}


